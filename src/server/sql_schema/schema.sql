CREATE EXTENSION IF NOT EXISTS ltree;

CREATE OR REPLACE FUNCTION perm_to_numeric ( m_owner INT, m_group INT, m_other INT )
RETURNS INT AS $$
BEGIN RETURN cast((m_owner << 6) | (m_group << 3 | m_other << 0) AS INT); END $$
LANGUAGE plpgsql IMMUTABLE COST 1;

CREATE OR REPLACE FUNCTION unix_to_numeric (unixperm VARCHAR)
RETURNS INT AS $$
DECLARE txt CHAR(3);
BEGIN
  txt := right(unixperm, 3);
  RETURN perm_to_numeric(cast(substring(txt, 1, 1) AS INT), cast(substring(txt, 2, 1) AS INT), cast(substring(txt, 3, 1) AS INT));
END $$
LANGUAGE plpgsql IMMUTABLE COST 1;

--create types
DO $$
BEGIN
    IF NOT EXISTS (SELECT 1 FROM pg_type WHERE typname = 'parameter_type') THEN
        CREATE TYPE parameter_type AS ENUM
        ( 'stored','pointed');
    END IF;

--    IF NOT EXISTS (SELECT 1 FROM pg_type WHERE typname = 'privilege_role') THEN
--        CREATE TYPE privilege_role AS ENUM
--        ();
--    END IF;

--    IF NOT EXISTS (SELECT 1 FROM pg_type WHERE typname = 'privilege_type') THEN
--        CREATE TYPE privilege_type AS ENUM
--        ();
--    END IF;
    --more types here...
END$$;

drop table if exists stat cascade;
drop table if exists action cascade;
drop table if exists metric_systems cascade;
drop table if exists measurands cascade;
drop table if exists privilege cascade;
drop table if exists pointed_values cascade;

drop table if exists category_files;
drop table if exists units_conversions;
drop table if exists in_stock;
drop table if exists implemented_action;
drop table if exists inventories_history;
drop table if exists user_history;
drop table if exists item_files;
drop table if exists packages_files;
drop table if exists system_info;
drop table if exists user_inventories;

create table system_info(
    id serial not null primary key,
    name text,
    value text
);

CREATE INDEX system_info_name ON system_info ( name ) WITH ( FILLFACTOR=100 );
COMMENT ON TABLE system_info IS 'table introduced to save information about system e.g. actual db version etc';

create table action (
    title           text      NOT NULL  CHECK( length(title) >= 3 AND length(title) < 100 ),
    apply_object    boolean   NOT NULL,
    PRIMARY KEY (title, apply_object)
);
COMMENT ON COLUMN action.title          IS 'column contains name of action';
COMMENT ON COLUMN action.apply_object   IS 'column specifies whether an action applies to objects or tables. Certain actions, like “create,” apply only to tables. I find the system is easier to manage if I choose my actions so they can only apply to one or the other, not both.';

create table stat (
    uid             serial not null unique primary key,
    owner           INT not null default 1,
    stat_group      INT not null default 2, -- 1 is a root usergroup, 2 is 'users' set as default
    unixperms       INT not null default unix_to_numeric('764'),
    status          INT not null default 0,
    name            TEXT NOT NULL CHECK( length(name) < 4096 ),
    creation_date   TIMESTAMP DEFAULT now() NOT NULL,
    last_update     TIMESTAMP
);

COMMENT ON COLUMN stat.uid          IS 'unique uid for all objects in database';
COMMENT ON COLUMN stat.owner        IS 'uid of object''s owner';
COMMENT ON COLUMN stat.stat_group   IS 'groups of object';
COMMENT ON COLUMN stat.unixperms    IS 'Unixpermissions';
COMMENT ON COLUMN stat.status       IS 'status in which object is in (login, logout, removed etc)';


create table implemented_action (
    table_name     text    not null,
    action    text    not null, -- TODO check if value is in action table
    status    int    not null,
    primary key (table_name, action, status)
);


create table privilege (
    role                    varchar(30)     not null, -- TODO change to enum
    who                     int             not null default 0,
    action                  text            not null,
    type                    varchar(30)     not null, -- TODO change in future to enum
    related_table_name      varchar(100)    not null,
    related_object_uid      int             not null default 0,
    primary key(role, who, action, type, related_table_name, related_object_uid)
);

CREATE INDEX privilege_index         ON privilege ( action, type) WITH ( FILLFACTOR=100 );
CREATE INDEX privilege_related_table ON privilege ( related_table_name ) WITH ( FILLFACTOR=100 );
CREATE INDEX privilege_action        ON privilege ( action )        WITH ( FILLFACTOR=100 );
CREATE INDEX privilege_type 	       ON privilege ( type )          WITH ( FILLFACTOR=100 );

COMMENT ON COLUMN privilege.role          IS 'specifies whether the privilege is granted to a user, a group, or in the case of an “object” privilege, the object’s owner or owner_group. A further special case, in my system, is “self.”';
COMMENT ON COLUMN privilege.who           IS 'is needed if role is user or group, and holds the user or group ID to which the privilege is granted.';
COMMENT ON COLUMN privilege.action 	      IS 'is the action the privilege grants. This is always required.';
COMMENT ON COLUMN privilege.type 	      IS 'specifies whether the privilege is “object”, “table”, or “global.”';
COMMENT ON COLUMN privilege.related_table_name IS 'holds the name of the table to which the privilege applies. This is always required, though in the case of a “self” privilege it’s redundant because a “self” privilege always applies to the t_user table.';
COMMENT ON COLUMN privilege.related_object_uid   IS 'stores the ID of the object to which the privilege applies, if it’s an object privilege. This has no meaning for table and global privileges, of course. The one applies to a table, not an object, and the second applies to all rows in a table, so an ID is immaterial. This is also not used for self privileges, because by definition a self privilege has to apply to the user requesting permission to do something.';


CREATE TABLE users (
    password          CHAR(128)       NOT NULL,
    salt              CHAR(128)       NOT NULL,
    email             VARCHAR(255)    NOT NULL UNIQUE CHECK ( email ~* '^[A-Za-z0-9._%-]+@[A-Za-z0-9.-]+[.][A-Za-z]+$' ) ,
    phonenumber       VARCHAR(20),
    address           TEXT            CHECK( length(address) <= 1000 ),
    description       TEXT            CHECK( length(description) <= 100000),   -- max size of description set to
    config            jsonb           DEFAULT ('{}'),
    avatar            TEXT,
    CONSTRAINT users_pkey         PRIMARY KEY (uid),
    CONSTRAINT users_unique UNIQUE(name)
) INHERITS (stat);

CREATE TABLE user_history (
    id serial not null primary key,
    uid int REFERENCES users(uid) ON DELETE CASCADE DEFERRABLE INITIALLY IMMEDIATE,
    action TEXT,
    when_happend TIMESTAMP DEFAULT(now())
);

COMMENT ON TABLE user_history IS 'saves user actions like login/logout';

CREATE TABLE files (
    file_size   BIGINT  NOT NULL,
    file_hash   TEXT    NOT NULL CHECK(length(file_hash) < 512 ),
    mimetype    TEXT    NOT NULL CHECK(length(mimetype) < 256 ),
    CONSTRAINT files_pkey PRIMARY KEY (uid),
    CONSTRAINT fileownereowner_fk FOREIGN KEY (owner) REFERENCES users (uid) ON DELETE CASCADE DEFERRABLE INITIALLY IMMEDIATE
) INHERITS (stat);

CREATE TABLE categories(
    parent_category_id    INTEGER     REFERENCES categories(uid),
    description           TEXT        CHECK(length(description) < 100000 ),
    parent_path           LTREE,
    CONSTRAINT categories_pkey PRIMARY KEY (uid),
    CONSTRAINT categorieowner_fk FOREIGN KEY (owner) REFERENCES users (uid) DEFERRABLE INITIALLY IMMEDIATE
) INHERITS (stat);

CREATE INDEX categories_parent_path_idx ON categories USING GIST (parent_path);

COMMENT ON TABLE categories IS 'categories of items';
-- COMMENT ON COLUMN categories.c_hide IS 'hide group from user, when true';
-- COMMENT ON COLUMN categories.c_allow_recipe IS 'Shows that category can take recipie';
-- COMMENT ON COLUMN categories.c_allow_items IS 'hide group from user, when true';

CREATE UNIQUE INDEX categories_unique_names  ON categories ( parent_category_id, name );
CREATE UNIQUE INDEX categories_unique_parent ON categories ( parent_category_id, uid );

CREATE TABLE category_files (
    category_id INTEGER NOT NULL REFERENCES categories,
    file_id INTEGER NOT NULL REFERENCES files,
    CONSTRAINT category_files_pk PRIMARY KEY (category_id, file_id)
);

CREATE TABLE measurands(
    id serial not null unique primary key,
    name VARCHAR(32) not null unique,
    description text,
    dimension_symbol VARCHAR(10)
);

CREATE TABLE metric_systems(
    id serial not null unique primary key,
    name VARCHAR(32) not null unique,
    description text
);

COMMENT ON TABLE measurands IS 'Information about measured quantity length, time etc.';

CREATE TABLE units(
    symbol VARCHAR (20) NOT NULL,
    description TEXT CHECK(length(description) < 100000),
    measurand_id int REFERENCES measurands(id),
    base_unit int REFERENCES units(uid),
    metric_system int REFERENCES metric_systems(id),
    CONSTRAINT units_pkey PRIMARY KEY (uid),
    CONSTRAINT unitowner_fk FOREIGN KEY (owner) REFERENCES users (uid) DEFERRABLE INITIALLY IMMEDIATE,
    CONSTRAINT units_unique UNIQUE(name, symbol)
) inherits(stat);

COMMENT ON TABLE units IS 'Table holds information about units used in application';
COMMENT ON COLUMN units.name IS 'Parameter name e.g. Ampere';
COMMENT ON COLUMN units.symbol IS 'Parameter symbol e.g. A';
COMMENT ON COLUMN units.description IS 'Simple description';

CREATE TABLE units_conversions(
    from_unit  INTEGER NOT NULL REFERENCES units(uid),
    to_unit    INTEGER NOT NULL REFERENCES units(uid),
    equation   TEXT NOT NULL,
    CONSTRAINT unit_conversions_unique PRIMARY KEY (from_unit, to_unit)
);
COMMENT ON TABLE units_conversions IS 'This table contains a mathematical equation for converting one unitl to other, more info available at http://www.partow.net/programming/exprtk/index.html';
COMMENT ON COLUMN units_conversions.equation IS 'this equation should be a proper exprtk equation';

CREATE TABLE pointed_values(
    id serial primary key,
    data jsonb default('{}')
);
CREATE INDEX items_pointed_values_idx ON pointed_values USING GIN (data);

CREATE TABLE parameters (
    symbol VARCHAR(20),
    unit INTEGER REFERENCES units(uid),
    description TEXT CHECK(length(description) < 100000),
    ptype parameter_type default('stored'),
    CONSTRAINT parameters_pkey PRIMARY KEY (uid),
    CONSTRAINT parametereowner_fk FOREIGN KEY (owner) REFERENCES users (uid) DEFERRABLE INITIALLY IMMEDIATE,
    CONSTRAINT parameters_unique UNIQUE(name, symbol)
) INHERITS (stat);

COMMENT ON COLUMN parameters.name   IS 'Parameter name e.g. "Load current max." ';
COMMENT ON COLUMN parameters.symbol IS 'Parameter symbol e.g. "I<sub>R</sub>';
COMMENT ON COLUMN parameters.unit   IS 'Parameter unit e.g. id od Amper unit from unit table';
COMMENT ON COLUMN parameters.ptype  IS '''stored'' parameter is a parameter which value is stored directly in items table, ''pointed'' means that the value of parameter is an ID of value stored in parameter_values table';

--CREATE TABLE producers (
--    description TEXT
--) INHERITS (stat)

CREATE TABLE items (
    producer      TEXT,
    category_id   INTEGER NOT NULL REFERENCES categories(uid),
    symbol        VARCHAR(300) NOT NULL,
    is_public     boolean DEFAULT(false),
--    name_scope    VARCHAR(64) DEFAULT 'std' NOT NULL,
    stored_values    jsonb NOT NULL DEFAULT('{}'),
    pointed_values INTEGER REFERENCES pointed_values(id),
    description   TEXT,
    CONSTRAINT items_pkey PRIMARY KEY (uid),
    CONSTRAINT itemowner_fk FOREIGN KEY (owner) REFERENCES users (uid) DEFERRABLE INITIALLY IMMEDIATE
) INHERITS (stat);

CREATE UNIQUE INDEX items_unique ON items(name, symbol, is_public);
CREATE INDEX items_stored_values_idx ON items USING GIN (stored_values);

CREATE TABLE item_files (
    item_id INTEGER NOT NULL REFERENCES items,
    file_id INTEGER NOT NULL REFERENCES files,
    CONSTRAINT items_files_pk PRIMARY KEY (item_id, file_id)
);

CREATE TABLE inventories(
    description TEXT CHECK(length(description)< 100000),
    CONSTRAINT inventories_pkey PRIMARY KEY (uid),
    CONSTRAINT inventoryowner_fk FOREIGN KEY (owner) REFERENCES users (uid) DEFERRABLE INITIALLY IMMEDIATE,
    CONSTRAINT inventories_name_length CHECK (length(name) < 100)
) INHERITS (stat);

CREATE TABLE user_inventories(
    inventory_id INTEGER NOT NULL REFERENCES inventories  ON DELETE CASCADE,
    user_id INTEGER NOT NULL REFERENCES users ON DELETE CASCADE,
    CONSTRAINT user_inventories_pk PRIMARY KEY (inventory_id, user_id)
);

CREATE TABLE shelfs(
    description TEXT CHECK( length( description ) < 100000),
    inventory_id INTEGER NOT NULL REFERENCES inventories ON DELETE CASCADE,
    CONSTRAINT shelf_owner_fk FOREIGN KEY (owner) REFERENCES users (uid) DEFERRABLE INITIALLY IMMEDIATE,
    CONSTRAINT shelfs_pkey PRIMARY KEY (uid)
) INHERITS (stat);

create table in_stock(
    item_id INTEGER NOT NULL REFERENCES items,
    inventory_id INTEGER NOT NULL REFERENCES inventories,
    amount numeric(10,10) NOT NULL DEFAULT 0
);

COMMENT ON TABLE in_stock IS 'Table contains information about items being available in storage';

create table inventories_operations(
    CONSTRAINT inventories_operations_pkey PRIMARY KEY (uid),
    CONSTRAINT OperationOwner_fk FOREIGN KEY (owner) REFERENCES users (uid) DEFERRABLE INITIALLY IMMEDIATE,
    CONSTRAINT inventory_operation_unique UNIQUE (name)
) INHERITS(stat);

create table inventories_history(
    inventory_from_id INTEGER NOT NULL REFERENCES inventories ON DELETE CASCADE,
    inventory_to_id INTEGER NOT NULL REFERENCES inventories ON DELETE CASCADE,
    operation_id INTEGER NOT NULL REFERENCES inventories_Operations ON DELETE CASCADE ,
    amount NUMERIC(10,10),

    date timestamp not null default now()
);

-- CREATE INDEX users_stat_index 	ON users 	(uid, owner, stat_group, unixperms, status) WITH ( FILLFACTOR=100 );
-- CREATE INDEX categories_stat_index 	ON categories 	(uid, owner, stat_group, unixperms, status) WITH ( FILLFACTOR=100 );
-- CREATE INDEX storages_stat_index 	ON storages 	(uid, owner, stat_group, unixperms, status) WITH ( FILLFACTOR=100 );
-- CREATE INDEX files_stat_index 	ON files 	(uid, owner, stat_group, unixperms, status) WITH ( FILLFACTOR=100 );
-- CREATE INDEX items_stat_index 	ON items 	(uid, owner, stat_group, unixperms, status) WITH ( FILLFACTOR=100 );

CREATE OR REPLACE FUNCTION last_update_column()
RETURNS TRIGGER AS $$
BEGIN
    NEW.last_update = now();
    RETURN NEW;
END;
$$ language 'plpgsql';

CREATE TRIGGER update_stat_las_update BEFORE UPDATE ON  stat FOR EACH ROW EXECUTE PROCEDURE  last_update_column();
CREATE TRIGGER update_user_las_update BEFORE UPDATE ON users FOR EACH ROW EXECUTE PROCEDURE  last_update_column();
CREATE TRIGGER update_item_las_update BEFORE UPDATE ON items FOR EACH ROW EXECUTE PROCEDURE  last_update_column();
CREATE TRIGGER update_files_las_update BEFORE UPDATE ON files FOR EACH ROW EXECUTE PROCEDURE  last_update_column();
CREATE TRIGGER update_categories_las_update BEFORE UPDATE ON categories FOR EACH ROW EXECUTE PROCEDURE  last_update_column();
--CREATE TRIGGER update_packages_las_update BEFORE UPDATE ON packages FOR EACH ROW EXECUTE PROCEDURE  last_update_column();
CREATE TRIGGER update_units_las_update BEFORE UPDATE ON units FOR EACH ROW EXECUTE PROCEDURE  last_update_column();
CREATE TRIGGER update_items_las_update BEFORE UPDATE ON items FOR EACH ROW EXECUTE PROCEDURE  last_update_column();
CREATE TRIGGER update_inventories_las_update BEFORE UPDATE ON inventories FOR EACH ROW EXECUTE PROCEDURE  last_update_column();
CREATE TRIGGER update_shelfs_las_update BEFORE UPDATE ON shelfs FOR EACH ROW EXECUTE PROCEDURE  last_update_column();
CREATE TRIGGER update_inventories_operations_las_update BEFORE UPDATE ON inventories_operations FOR EACH ROW EXECUTE PROCEDURE  last_update_column();



CREATE OR REPLACE FUNCTION update_category_parent_path() RETURNS TRIGGER AS $$
    DECLARE
        path ltree;
    BEGIN
        IF NEW.parent_category_id IS NULL THEN
            NEW.parent_path = 'root'::ltree;
        ELSEIF TG_OP = 'INSERT' OR OLD.parent_category_id IS NULL OR OLD.parent_category_id != NEW.parent_category_id THEN
            SELECT parent_path || uid::text FROM categories WHERE uid = NEW.parent_category_id INTO path;
            IF path IS NULL THEN
                RAISE EXCEPTION 'Invalid parent_id %', NEW.parent_category_id;
            END IF;
            NEW.parent_path = path;
        END IF;
        RETURN NEW;
    END;
$$ LANGUAGE plpgsql;


CREATE TRIGGER parent_path_tgr
    BEFORE INSERT OR UPDATE ON categories
    FOR EACH ROW EXECUTE PROCEDURE update_category_parent_path();

CREATE OR REPLACE FUNCTION objects_with_action (m_tab VARCHAR, m_action varchar, userid int)
RETURNS setof int AS $$

DECLARE r int;
DECLARE usergroups INT;
DECLARE groupsroot INT;
DECLARE tablename VARCHAR(255);

BEGIN
  SELECT stat_group
  FROM users
  WHERE uid = userid
  INTO usergroups;

  groupsroot := 1;

  FOR
  r IN
execute 'select distinct obj.uid
from ' || m_tab ||' as obj
inner join implemented_action as ia
on ia.table_name ='''|| m_tab || '''
and ia.action = '''|| m_action ||'''
and ((ia.status = 0) or (ia.status & obj.status <> 0))
inner join action as ac
on ac.title = '''|| m_action ||'''
left outer join privilege as pr
on pr.related_table_name = '''|| m_tab || '''
and pr.action =  '''|| m_action ||'''
and (
(pr.type = ''object'' and pr.related_object_uid = obj.uid)
or pr.type = ''global''
or (pr.role = ''self'' and ' || userid || ' = obj.uid and '''|| m_tab || ''' = ''users''))
  WHERE ac.apply_object
        AND (
          (' || usergroups || ' & ' || groupsroot || ' <> 0)
          OR (
            ac.title = ''read''
            AND (
              (obj.unixperms & 4 <> 0)
              OR (
                (obj.unixperms & 256 <> 0)
                AND obj.owner = ' || userid || '
                )
              OR (
                (obj.unixperms & 32 <> 0)
                AND (' || usergroups || ' & obj.stat_group <> 0)
                )
              )
            )
          OR (
            ac.title = ''write''
            AND (
              (obj.unixperms & 2 <> 0)
              OR (
                (obj.unixperms & 128 <> 0)
                AND obj.owner = ' || userid || '
                )
              OR (
                (obj.unixperms & 16 <> 0)
                AND (' || usergroups || ' & obj.stat_group <> 0)
                )
              )
            )
          OR (
            ac.title = ''delete''
            AND (
              (obj.unixperms & 1 <> 0)
              OR ((obj.unixperms & 64 <> 0) AND obj.owner = ' || userid || ')
              OR ((obj.unixperms & 8  <> 0) AND (' || usergroups || ' & obj.stat_group <> 0))
              )
            )
          OR (
            pr.role = ''user''
            AND pr.who = ' || userid || '
            )
          OR (
            pr.role = ''owner''
            AND obj.owner = ' || userid || '
            )
          OR (
            pr.role = ''owner_group''
            AND (obj.stat_group & ' || usergroups || ' <> 0)
            )
          OR (
            pr.role = ''group''
            AND (pr.who & ' || usergroups || ' <> 0)
            )
          )
        OR pr.role = ''self'' '

  LOOP
  RETURN NEXT r;
  end loop;
END $$
LANGUAGE plpgsql  ;

-- insert needed data into dataase

DO
$$
DECLARE lastid int;

BEGIN

END $$;
