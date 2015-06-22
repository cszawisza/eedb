
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

-- update t_users set c_password = crypt('text', gen_salt('bf')) where c_uid = 1;
-- select (c_password = crypt('text', c_password)) AS pswmatch FROM t_users where c_uid = 1;

drop table if exists t_inventories_history;
drop table if exists t_inventories_operations;
drop table if exists t_in_stock;
drop table if exists t_inventories_racks;
drop table if exists t_user_inventories;
drop table if exists t_inventories;
drop table if exists t_item_files;
drop table if exists t_items;
drop table if exists t_parameters;
drop table if exists t_packages_files;
drop table if exists t_packages;
drop table if exists t_category_files;
drop table if exists t_categories;
drop table if exists t_files;
drop table if exists t_users;
drop table if exists t_privilege;
drop table if exists t_implemented_action;
drop table if exists t_acl;
drop table if exists t_action;


create table t_action (
    c_title           text      NOT NULL  CHECK( length(c_title) >= 3 AND length(c_title) < 100 ),
    c_apply_object    boolean   NOT NULL,
    PRIMARY KEY (c_title, c_apply_object)
);
COMMENT ON COLUMN t_action.c_title          IS 'column contains name of action';
COMMENT ON COLUMN t_action.c_apply_object   IS 'column specifies whether an action applies to objects or tables. Certain actions, like “create,” apply only to tables. I find the system is easier to manage if I choose my actions so they can only apply to one or the other, not both.';

create table t_acl (
    c_uid             serial not null primary key,
    c_owner           int not null default 1,
    c_group           int not null default 2, -- 1 is a root usergroup, 2 is 'users' set as default
    c_unixperms       int not null default unix_to_numeric('764'),
    c_status          int not null default 0
);

COMMENT ON COLUMN t_acl.c_uid       IS 'unique uid for all objects in database';
COMMENT ON COLUMN t_acl.c_owner     IS 'uid of object''s owner';
COMMENT ON COLUMN t_acl.c_group     IS 'groups of object';
COMMENT ON COLUMN t_acl.c_unixperms IS 'Unixpermissions';
COMMENT ON COLUMN t_acl.c_status    IS 'status in which object is in (login, logout, removed etc)';


create table t_implemented_action (
    c_table     text    not null,
    c_action    text    not null, -- TODO check if value is in t_action table
    c_status    int    not null,
    primary key (c_table, c_action)
);


create table t_privilege (
    c_role            varchar(30)     not null, -- TODO change to enum
    c_who             int             not null default 0,
    c_action          text            not null,
    c_type            varchar(30)     not null, -- TODO change in future to enum
    c_related_table   varchar(100)    not null,
    c_related_uid     int             not null default 0,
    primary key(c_role, c_who, c_action, c_type, c_related_table, c_related_uid)
);

CREATE INDEX t_privilege_index         ON t_privilege ( c_action, c_type) WITH ( FILLFACTOR=100 );
CREATE INDEX t_privilege_related_table ON t_privilege ( c_related_table ) WITH ( FILLFACTOR=100 );
CREATE INDEX t_privilege_action        ON t_privilege ( c_action )        WITH ( FILLFACTOR=100 );
CREATE INDEX t_privilege_type 	       ON t_privilege ( c_type )          WITH ( FILLFACTOR=100 );

COMMENT ON COLUMN t_privilege.c_role          IS 'specifies whether the privilege is granted to a user, a group, or in the case of an “object” privilege, the object’s owner or owner_group. A further special case, in my system, is “self.”';
COMMENT ON COLUMN t_privilege.c_who           IS 'is needed if c_role is user or group, and holds the user or group ID to which the privilege is granted.';
COMMENT ON COLUMN t_privilege.c_action 	      IS 'is the action the privilege grants. This is always required.';
COMMENT ON COLUMN t_privilege.c_type 	      IS 'specifies whether the privilege is “object”, “table”, or “global.”';
COMMENT ON COLUMN t_privilege.c_related_table IS 'holds the name of the table to which the privilege applies. This is always required, though in the case of a “self” privilege it’s redundant because a “self” privilege always applies to the t_user table.';
COMMENT ON COLUMN t_privilege.c_related_uid   IS 'stores the ID of the object to which the privilege applies, if it’s an object privilege. This has no meaning for table and global privileges, of course. The one applies to a table, not an object, and the second applies to all rows in a table, so an ID is immaterial. This is also not used for self privileges, because by definition a self privilege has to apply to the user requesting permission to do something.';


CREATE TABLE t_users (
    c_name              VARCHAR(72)     NOT NULL UNIQUE CHECK( length(c_name) >= 2 ),
    c_password          CHAR(128)       NOT NULL,
    c_salt              CHAR(128)       NOT NULL,
    c_email             VARCHAR(255)    NOT NULL UNIQUE CHECK ( c_email ~* '^[A-Za-z0-9._%-]+@[A-Za-z0-9.-]+[.][A-Za-z]+$' ) ,
    c_phonenumber       VARCHAR(20),
    c_address           TEXT            CHECK( length(c_address) <= 1000 ),
    c_description       TEXT            CHECK( length(c_description) <= 100000),   -- max size of description set to
    c_registrationdate  TIMESTAMP       DEFAULT now() NOT NULL,
    c_lastlogin         TIMESTAMP       CHECK( c_lastlogin <= now() ),
    c_badpasswd         INT             DEFAULT 0,
    c_config            json            DEFAULT ('{}'),
    CONSTRAINT t_users_pkey         PRIMARY KEY (c_uid)
) INHERITS (t_acl);

CREATE TABLE t_files (
    c_name      TEXT    NOT NULL CHECK(length(c_name) < 4096 ),
    c_size      BIGINT  NOT NULL,
    c_sha       TEXT    NOT NULL CHECK(length(c_sha) < 512 ),
    c_mimetype  TEXT    NOT NULL CHECK(length(c_mimetype) < 256 ),
    CONSTRAINT t_files_pkey PRIMARY KEY (c_uid),
    CONSTRAINT t_fileownereowner_fk FOREIGN KEY (c_owner) REFERENCES t_users (c_uid) DEFERRABLE INITIALLY IMMEDIATE
) INHERITS (t_acl);

CREATE TABLE t_categories(
    c_parent_category_id    INTEGER     REFERENCES t_categories(c_uid),
    c_name                  TEXT        NOT NULL CHECK(length(c_name) < 100 ),
    c_description           TEXT        CHECK(length(c_description) < 100000 ),
    c_creationDate          TIMESTAMP   DEFAULT NOW() NOT NULL,
    c_allow_recipe          BOOLEAN     DEFAULT false NOT NULL,
    c_allow_items           BOOLEAN     DEFAULT true NOT NULL,
    c_hide                  BOOLEAN     DEFAULT false,
    CONSTRAINT t_categories_pkey PRIMARY KEY (c_uid),
    CONSTRAINT t_categorieowner_fk FOREIGN KEY (c_owner) REFERENCES t_users (c_uid) DEFERRABLE INITIALLY IMMEDIATE
) INHERITS (t_acl);


COMMENT ON COLUMN t_categories.c_hide IS 'hide group from user, when true';

CREATE UNIQUE INDEX t_categories_unique_names  ON t_categories ( c_parent_category_id, c_name );
CREATE UNIQUE INDEX t_categories_unique_parent ON t_categories ( c_parent_category_id, c_uid );

CREATE TABLE t_category_files (
    c_category_id INTEGER NOT NULL REFERENCES t_categories,
    c_file_id INTEGER NOT NULL REFERENCES t_files,
    CONSTRAINT category_files_pk PRIMARY KEY (c_category_id, c_file_id)
);

CREATE TABLE t_packages (
    c_name          TEXT NOT NULL CHECK(length(c_name) < 256 ),
    c_pinNr         INTEGER,
    c_mountType     TEXT CHECK(length(c_mountType) < 100 ), -- TODO move to seperate table?
    c_config        json,
    CONSTRAINT packages_pkey PRIMARY KEY (c_uid)
) INHERITS (t_acl);

CREATE TABLE t_packages_files (
    c_package_id INTEGER NOT NULL REFERENCES t_packages,
    c_file_id INTEGER NOT NULL REFERENCES t_files,
    CONSTRAINT packages_files_pk PRIMARY KEY (c_package_id, c_file_id)
);

CREATE TABLE t_parameters (
    c_name VARCHAR(64) NOT NULL,
    c_symbol VARCHAR(16),
    c_config json NOT NULL DEFAULT ('{}'),
    c_description TEXT,
    c_unixperms int not null default unix_to_numeric('766'),
    CONSTRAINT t_parameters_pkey PRIMARY KEY (c_uid),
    CONSTRAINT t_parametereowner_fk FOREIGN KEY (c_owner) REFERENCES t_users (c_uid) DEFERRABLE INITIALLY IMMEDIATE
) INHERITS (t_acl);

CREATE UNIQUE INDEX t_parameters_unique ON t_parameters ( c_name, c_symbol );

CREATE TABLE t_items (
    c_package_id    INTEGER NOT NULL REFERENCES t_packages(c_uid),
    c_category_id   INTEGER NOT NULL REFERENCES t_categories(c_uid),
    c_name          VARCHAR(255) NOT NULL,
    c_symbol        VARCHAR(255) NOT NULL,
    c_namespace     VARCHAR(64) DEFAULT 'std' NOT NULL,
    c_creationDate  TIMESTAMP DEFAULT now() NOT NULL,
    c_update        TIMESTAMP NOT NULL,
    c_parameters    json NOT NULL,
    c_description   TEXT,
    CONSTRAINT t_items_pkey PRIMARY KEY (c_uid),
    CONSTRAINT t_itemowner_fk FOREIGN KEY (c_owner) REFERENCES t_users (c_uid) DEFERRABLE INITIALLY IMMEDIATE
) INHERITS (t_acl);

CREATE UNIQUE INDEX t_items_unique ON t_items(c_name, c_symbol, c_namespace);

CREATE TABLE t_item_files (
    c_item_id INTEGER NOT NULL REFERENCES t_items,
    c_file_id INTEGER NOT NULL REFERENCES t_files,
    CONSTRAINT t_items_files_pk PRIMARY KEY (c_item_id, c_file_id)
);

CREATE TABLE t_inventories(
    c_name VARCHAR(255) NOT NULL UNIQUE,
    -- creation date, other info
    CONSTRAINT t_inventories_pkey PRIMARY KEY (c_uid),
    CONSTRAINT t_inventoryowner_fk FOREIGN KEY (c_owner) REFERENCES t_users (c_uid) DEFERRABLE INITIALLY IMMEDIATE
) INHERITS (t_acl);

CREATE TABLE t_user_inventories(
    c_inventory_id INTEGER NOT NULL REFERENCES t_inventories,
    c_user_id INTEGER NOT NULL REFERENCES t_users,
    CONSTRAINT tuser_inventories_pk PRIMARY KEY (c_inventory_id, c_user_id)
);

CREATE TABLE t_inventories_racks(
    c_storage_id INTEGER NOT NULL REFERENCES t_inventories,
    c_name varchar(100) NOT NULL UNIQUE,
    CONSTRAINT rackOwner_fk FOREIGN KEY (c_owner) REFERENCES t_users (c_uid) DEFERRABLE INITIALLY IMMEDIATE
) INHERITS (t_acl);

create table t_in_stock(
    c_item_id INTEGER NOT NULL REFERENCES t_items,
    c_inventory_id INTEGER NOT NULL REFERENCES t_inventories,
    c_amount numeric(10,10) NOT NULL DEFAULT 0
);

COMMENT ON TABLE t_in_stock IS 'Table contains information about items being available in storage';

create table t_inventories_operations(
    c_name varchar(50) not null unique,
    CONSTRAINT t_inventories_operations_pkey PRIMARY KEY (c_uid),
    CONSTRAINT OperationOwner_fk FOREIGN KEY (c_owner) REFERENCES t_users (c_uid) DEFERRABLE INITIALLY IMMEDIATE
) INHERITS(t_acl);

create table t_inventories_history(
    c_inventory_from_id INTEGER NOT NULL REFERENCES t_inventories,
    c_inventory_to_id INTEGER NOT NULL REFERENCES t_inventories,
    c_operation_id INTEGER NOT NULL REFERENCES t_inventories_Operations,
    c_amount NUMERIC(10,10),

    date timestamp not null default now()
);

-- CREATE INDEX users_acl_index 	ON users 	(c_uid, c_owner, c_group, c_unixperms, c_status) WITH ( FILLFACTOR=100 );
-- CREATE INDEX categories_acl_index 	ON categories 	(c_uid, c_owner, c_group, c_unixperms, c_status) WITH ( FILLFACTOR=100 );
-- CREATE INDEX storages_acl_index 	ON storages 	(c_uid, c_owner, c_group, c_unixperms, c_status) WITH ( FILLFACTOR=100 );
-- CREATE INDEX files_acl_index 	ON files 	(c_uid, c_owner, c_group, c_unixperms, c_status) WITH ( FILLFACTOR=100 );
-- CREATE INDEX packages_acl_index 	ON packages 	(c_uid, c_owner, c_group, c_unixperms, c_status) WITH ( FILLFACTOR=100 );
-- CREATE INDEX items_acl_index 	ON items 	(c_uid, c_owner, c_group, c_unixperms, c_status) WITH ( FILLFACTOR=100 );
-- CREATE INDEX parameters_acl_index 	ON parameters 	(c_uid, c_owner, c_group, c_unixperms, c_status) WITH ( FILLFACTOR=100 );


DO $$
DECLARE rootuserid int;
DECLARE testuserid int;
BEGIN
  -- root user MUST be insert as first in the whole database!
  insert into t_users (c_name, c_password, c_salt, c_email)
        values('ROOT','pass','salt', 'email1@ww.ww') returning c_uid into rootuserid;

  insert into t_categories(c_parent_category_id, c_name, c_allow_recipe, c_allow_items, c_owner) values
        (NULL, 'Root', false, false, rootuserid);

-- can be deleted later, only for testing
  insert into t_users (c_name, c_password, c_salt, c_email) values
  ('test_user','pass','salt','test_email@ww.ww') returning c_uid into testuserid;
  insert into t_users (c_name, c_password, c_salt, c_email) values
  ('test_user2','pass2','salt','test_email2@ww.ww');

  insert into t_action(c_title, c_apply_object) values
        ('stat'         , true),
        ('stat'         , false),
        ('chmod'        , true),
        ('chmod'        , false),
        ('chgrp'        , true),
        ('chgrp'        , false),
        ('chown'        , true),
        ('chown'        , false),
        ('view_acl'     , true),
        ('view_acl'     , false),

        ('read'         , true),
        ('write'        , true),
        ('delete'       , true),
        ('read'         , false),
        ('write'        , false),
        ('login'        , true),
        ('update_passwd', true);

  insert into t_implemented_action
        (c_table        , c_action       , c_status) values
        ('t_users'      , 'login'        , 0 ),
        ('t_users'      , 'update_passwd', 0 ),
        ('t_users'      , 'read'         , 0 ),
        ('t_users'      , 'write'        , 0 ),
        ('t_users'      , 'delete'       , 0 ),
        ('t_files'      , 'read'         , 0 ),
        ('t_files'      , 'write'        , 0 ),
        ('t_files'      , 'delete'       , 0 );

-- c_role = user,owner, owner_group, group, self
-- c_type = object, global
  insert into t_privilege
        (c_role, c_who, c_action       , c_type    , c_related_table, c_related_uid) values
        ('self', 0    , 'update_passwd', 'object'  , 't_users'      , 0),
        ('self', 0    , 'login'        , 'object'  , 't_users'      , 0);

END $$;

CREATE
  OR REPLACE FUNCTION get_user_perrmssions_for_table (
  userid INT
  ,tablename VARCHAR(255)
  )
RETURNS setof VARCHAR AS $$

DECLARE usergroups INT;

BEGIN
  SELECT c_group
  FROM t_acl
  WHERE c_uid = userid
  INTO usergroups;

return query

      SELECT ac.c_title
      FROM t_action AS ac
      -- Privileges that apply to the table and grant the given action
      -- Not an inner join because the action may be granted even if there is no
      -- privilege granting it. For example, root users can take all actions.
      LEFT JOIN t_privilege AS pr ON pr.c_related_table = tablename
        AND pr.c_action = ac.c_title
        AND pr.c_type = 'table'
      WHERE
        -- The action must apply to tables (NOT apply to objects)
        (ac.c_apply_object = false)
        AND (
          -- Members of the 'root' group are always allowed to do everything
          (usergroups & 1 <> 0)
          -- user privileges
          OR (
            pr.c_role = 'user'
            AND pr.c_who = userid
            )
          -- group privileges
          OR (
            pr.c_role = 'group'
            AND (pr.c_who & usergroups <> 0)
            )
          );
END $$
LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION objects_with_action (m_tab VARCHAR, m_action varchar, userid int)
RETURNS setof int AS $$

DECLARE r int;
DECLARE usergroups INT;
DECLARE groupsroot INT;
DECLARE tablename VARCHAR(255);

BEGIN
  SELECT c_group
  FROM users
  WHERE c_uid = userid
  INTO usergroups;

  groupsroot := 1;

  FOR
  r IN
execute 'select distinct obj.c_uid
from ' || m_tab ||' as obj
inner join t_implemented_action as ia
on ia.c_table ='''|| m_tab || '''
and ia.c_action = '''|| m_action ||'''
and ((ia.c_status = 0) or (ia.c_status & obj.c_status <> 0))
inner join t_action as ac
on ac.c_title = '''|| m_action ||'''
left outer join t_privilege as pr
on pr.c_related_table = '''|| m_tab || '''
and pr.c_action =  '''|| m_action ||'''
and (
(pr.c_type = ''object'' and pr.c_related_uid = obj.c_uid)
or pr.c_type = ''global''
or (pr.c_role = ''self'' and ' || userid || ' = obj.c_uid and '''|| m_tab || ''' = ''users''))
  WHERE ac.c_apply_object
        AND (
          (' || usergroups || ' & ' || groupsroot || ' <> 0)
          OR (
            ac.c_title = ''read''
            AND (
              (obj.c_unixperms & 4 <> 0)
              OR (
                (obj.c_unixperms & 256 <> 0)
                AND obj.c_owner = ' || userid || '
                )
              OR (
                (obj.c_unixperms & 32 <> 0)
                AND (' || usergroups || ' & obj.c_group <> 0)
                )
              )
            )
          OR (
            ac.c_title = ''write''
            AND (
              (obj.c_unixperms & 2 <> 0)
              OR (
                (obj.c_unixperms & 128 <> 0)
                AND obj.c_owner = ' || userid || '
                )
              OR (
                (obj.c_unixperms & 16 <> 0)
                AND (' || usergroups || ' & obj.c_group <> 0)
                )
              )
            )
          OR (
            ac.c_title = ''delete''
            AND (
              (obj.c_unixperms & 1 <> 0)
              OR ((obj.c_unixperms & 64 <> 0) AND obj.c_owner = ' || userid || ')
              OR ((obj.c_unixperms & 8  <> 0) AND (' || usergroups || ' & obj.c_group <> 0))
              )
            )
          OR (
            pr.c_role = ''user''
            AND pr.c_who = ' || userid || '
            )
          OR (
            pr.c_role = ''owner''
            AND obj.c_owner = ' || userid || '
            )
          OR (
            pr.c_role = ''owner_group''
            AND (obj.c_group & ' || usergroups || ' <> 0)
            )
          OR (
            pr.c_role = ''group''
            AND (pr.c_who & ' || usergroups || ' <> 0)
            )
          )
        OR pr.c_role = ''self'' '

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
