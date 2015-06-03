
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

drop table if exists t_status cascade;
drop table if exists t_action cascade;
drop table if exists t_acl cascade;
drop table if exists t_implemented_action;
drop table if exists t_privilege;
drop table if exists User_Storages;
drop table if exists Storage_History;
drop table if exists In_Stock;
drop table if exists packages_files cascade;
drop table if exists item_files cascade;
drop table if exists category_files cascade;

create table t_action (
    c_title           varchar(100) not null primary key,
    c_apply_object    boolean      not null
);
CREATE INDEX t_action_apply_object ON t_action (  c_apply_object );

create table t_status (
    c_uid             int not null primary key,
    c_name            varchar(100) not null
);

COMMENT ON COLUMN t_action.c_apply_object   IS 'column specifies whether an action applies to objects or tables. Certain actions, like “create,” apply only to tables. I find the system is easier to manage if I choose my actions so they can only apply to one or the other, not both.';
COMMENT ON COLUMN t_status.c_name           IS 'column contains name of status for rest of application';

create table t_acl (
    c_uid             serial not null primary key,
    c_owner           int not null default 1,
    c_group           int not null default 1,
    c_unixperms       int not null default unix_to_numeric('764'),
    c_status          int not null default 0
);

create table t_implemented_action (
    c_table           varchar(100)    not null,
    c_action          varchar(100)    not null,
    c_status          int             not null default 0, -- TODO change to t_status reference
    primary key (c_table, c_action)
);

create table t_privilege (
    c_role            varchar(30)     not null,
    c_who             int             not null default 0,
    c_action          varchar(100)    not null references t_action,
    c_type            varchar(30)     not null, -- TODO change in future to enum
    c_related_table   varchar(100)    not null,
    c_related_uid     int             not null default 0,
    primary key(c_role, c_who, c_action, c_type, c_related_table, c_related_uid)
);



CREATE INDEX t_privilege_index       ON t_privilege ( c_action, c_type);
CREATE INDEX privilege_related_table ON t_privilege (  c_related_table );
CREATE INDEX privilege_action        ON t_privilege (  c_action );
CREATE INDEX privilege_type 	     ON t_privilege (  c_type );


COMMENT ON COLUMN t_privilege.c_role          IS 'specifies whether the privilege is granted to a user, a group, or in the case of an “object” privilege, the object’s owner or owner_group. A further special case, in my system, is “self.”';
COMMENT ON COLUMN t_privilege.c_who           IS 'is needed if c_role is user or group, and holds the user or group ID to which the privilege is granted.';
COMMENT ON COLUMN t_privilege.c_action 	      IS 'is the action the privilege grants. This is always required.';
COMMENT ON COLUMN t_privilege.c_type 	      IS 'specifies whether the privilege is “object”, “table”, or “global.”';
COMMENT ON COLUMN t_privilege.c_related_table IS 'holds the name of the table to which the privilege applies. This is always required, though in the case of a “self” privilege it’s redundant because a “self” privilege always applies to the t_user table.';
COMMENT ON COLUMN t_privilege.c_related_uid   IS 'stores the ID of the object to which the privilege applies, if it’s an object privilege. This has no meaning for table and global privileges, of course. The one applies to a table, not an object, and the second applies to all rows in a table, so an ID is immaterial. This is also not used for self privileges, because by definition a self privilege has to apply to the user requesting permission to do something.';

CREATE TABLE users (
    name VARCHAR(34) NOT NULL UNIQUE,
    password CHAR(128) NOT NULL,
    email VARCHAR(255) NOT NULL UNIQUE,
    phonenumber VARCHAR(32),
    address TEXT,
    description TEXT,
    registrationdate TIMESTAMP DEFAULT now() NOT NULL,
    lastlogin TIMESTAMP,
    config json DEFAULT ('{}'),
    CONSTRAINT users_pkey PRIMARY KEY (c_uid)
) INHERITS (t_acl);


CREATE TABLE files (
    name VARCHAR(255) NOT NULL,
    size BIGINT NOT NULL,
    sha CHAR(512) NOT NULL,
    mimetype VARCHAR(255) NOT NULL,
    CONSTRAINT files_pkey PRIMARY KEY (c_uid),
    CONSTRAINT fileownereowner_fk FOREIGN KEY (c_owner) REFERENCES users (c_uid) DEFERRABLE INITIALLY IMMEDIATE
) INHERITS (t_acl);

CREATE TABLE categories(
    parent_category_id INTEGER REFERENCES categories(c_uid),
    name VARCHAR(64) NOT NULL,
    description TEXT,
    creationDate TIMESTAMP DEFAULT NOW() NOT NULL,
    allow_recipe BOOLEAN DEFAULT false NOT NULL,
    allow_items BOOLEAN DEFAULT true NOT NULL,
    CONSTRAINT categories_pkey PRIMARY KEY (c_uid),
    CONSTRAINT categorieowner_fk FOREIGN KEY (c_owner) REFERENCES users (c_uid) DEFERRABLE INITIALLY IMMEDIATE
) INHERITS (t_acl);

CREATE UNIQUE INDEX categories_unique ON categories ( parent_category_id, name );

CREATE TABLE category_files (
    category_id INTEGER NOT NULL REFERENCES categories,
    file_id INTEGER NOT NULL REFERENCES files,
    CONSTRAINT category_files_pk PRIMARY KEY (category_id, file_id)
);

CREATE TABLE packages (
    name VARCHAR(255) NOT NULL,
    pinNr INTEGER,
    mountType VARCHAR(32),
    config json,
    CONSTRAINT packages_pkey PRIMARY KEY (c_uid)
) INHERITS (t_acl);

CREATE TABLE packages_files (
    package_id INTEGER NOT NULL REFERENCES packages,
    file_id INTEGER NOT NULL REFERENCES files,
    CONSTRAINT packages_files_pk PRIMARY KEY (package_id, file_id)
);

CREATE TABLE parameters (
    name VARCHAR(64) NOT NULL,
    symbol VARCHAR(16),
    config json NOT NULL DEFAULT ('{}'),
    description TEXT,
    CONSTRAINT parameters_pkey PRIMARY KEY (c_uid),
    c_unixperms int not null default unix_to_numeric('766'),
    CONSTRAINT parametereowner_fk FOREIGN KEY (c_owner) REFERENCES users (c_uid) DEFERRABLE INITIALLY IMMEDIATE
) INHERITS (t_acl);

CREATE UNIQUE INDEX parameters_unique ON public.parameters ( name, symbol );

CREATE TABLE items (
    package_id INTEGER NOT NULL REFERENCES packages(c_uid),
    category_id INTEGER NOT NULL REFERENCES categories(c_uid),
    name VARCHAR(255) NOT NULL,
    symbol VARCHAR(255) NOT NULL,
    namespace VARCHAR(64) DEFAULT 'std' NOT NULL,
    creationDate TIMESTAMP DEFAULT now() NOT NULL,
    update TIMESTAMP NOT NULL,
    parameters json NOT NULL,
    description TEXT,
    CONSTRAINT items_pkey PRIMARY KEY (c_uid),
    CONSTRAINT itemowner_fk FOREIGN KEY (c_owner) REFERENCES users (c_uid) DEFERRABLE INITIALLY IMMEDIATE
) INHERITS (t_acl);

CREATE UNIQUE INDEX items_unique ON items(name, symbol, namespace);

CREATE TABLE Item_files (
    item_id INTEGER NOT NULL REFERENCES items,
    file_id INTEGER NOT NULL REFERENCES files,
    CONSTRAINT items_files_pk PRIMARY KEY (item_id, file_id)
);

CREATE TABLE Storages(
    name VARCHAR(255) NOT NULL UNIQUE,
    CONSTRAINT storages_pkey PRIMARY KEY (c_uid),
    CONSTRAINT storageowner_fk FOREIGN KEY (c_owner) REFERENCES users (c_uid) DEFERRABLE INITIALLY IMMEDIATE
) INHERITS (t_acl);

CREATE TABLE User_Storages(
    storage_id INTEGER NOT NULL REFERENCES Storages,
    user_id INTEGER NOT NULL REFERENCES Users,
    CONSTRAINT User_Storages_pk PRIMARY KEY (storage_id, user_id)
);

CREATE TABLE Storage_Racks(
    storage_id INTEGER NOT NULL REFERENCES Storages,
    name varchar(100) NOT NULL UNIQUE,
    CONSTRAINT rackOwner_fk FOREIGN KEY (c_owner) REFERENCES users (c_uid) DEFERRABLE INITIALLY IMMEDIATE
) INHERITS (t_acl);

create table In_Stock(
    item_id INTEGER NOT NULL REFERENCES items,
    storage_id INTEGER NOT NULL REFERENCES Storages,
    amount numeric(10,10) NOT NULL DEFAULT 0
);

COMMENT ON TABLE In_Stock IS '';

create table Storage_Operations(
    name varchar(50) not null unique,
    CONSTRAINT Storage_Operations_pkey PRIMARY KEY (c_uid),
    CONSTRAINT OperationOwner_fk FOREIGN KEY (c_owner) REFERENCES users (c_uid) DEFERRABLE INITIALLY IMMEDIATE
) INHERITS(t_acl);

create table Storage_History(
    storage_from_id INTEGER NOT NULL REFERENCES Storages,
    storage_to_id INTEGER NOT NULL REFERENCES Storages,
    operation_id INTEGER NOT NULL REFERENCES Storage_Operations,
    amount NUMERIC(10,10),
    
    date timestamp not null default now()
);

-- CREATE INDEX users_acl_index 		ON users 	(c_uid, c_owner, c_group, c_unixperms, c_status) WITH ( FILLFACTOR=100 );
-- CREATE INDEX categories_acl_index 	ON categories 	(c_uid, c_owner, c_group, c_unixperms, c_status) WITH ( FILLFACTOR=100 );
-- CREATE INDEX storages_acl_index 	ON storages 	(c_uid, c_owner, c_group, c_unixperms, c_status) WITH ( FILLFACTOR=100 );
-- CREATE INDEX files_acl_index 		ON files 	(c_uid, c_owner, c_group, c_unixperms, c_status) WITH ( FILLFACTOR=100 );
-- CREATE INDEX packages_acl_index 	ON packages 	(c_uid, c_owner, c_group, c_unixperms, c_status) WITH ( FILLFACTOR=100 );
-- CREATE INDEX items_acl_index 		ON items 	(c_uid, c_owner, c_group, c_unixperms, c_status) WITH ( FILLFACTOR=100 );
-- CREATE INDEX parameters_acl_index 	ON parameters 	(c_uid, c_owner, c_group, c_unixperms, c_status) WITH ( FILLFACTOR=100 );


DO $$
DECLARE rootuserid int;
DECLARE testuserid int;
BEGIN
  -- root user MUST be insert as first in the whole database!
  insert into users (name, password, email) values('ROOT','pass','email1@ww.ww') returning c_uid into rootuserid;
  insert into categories(parent_category_id, name, allow_recipe, allow_items, c_owner) values(NULL, 'Root', false, false, rootuserid);



-- can be deleted later, only for testing
  insert into users (name, password, email) values
  ('test_user','pass','test_email@ww.ww') returning c_uid into testuserid;
  insert into users (name, password, email) values
  ('test_user2','pass2','test_email2@ww.ww');

  insert into t_action(c_title, c_apply_object) values
        ('register'     , true),
        ('login'        , true),
        ('update'       , true),

        ('show'         , true),
        ('join'         , true),
        ('activate'     , true),
        ('passwd_update', true),
        ('list_all'     , false);
        
  insert into packages ( name ) values ('dummy');
  insert into t_privilege
        (c_role,  c_who     , c_action      , c_type    , c_related_table   , c_related_uid) values
        ('self' , 0         ,'passwd_update','object'   ,'users'            , 0);

insert into t_implemented_action
        (c_table     ,c_action, c_status) values
        ('users'     , 'register', 0),
        ('users'     , 'login' ,   0),
        ('users'     , 'update',   1),
        ('users'     , 'delete',   1),

        ('parameters', 'insert',   1),
        ('parameters', 'update',   1),

        ('files'     , 'activate', 2);

insert into items (c_unixperms, c_owner, package_id, category_id, name, symbol, update, parameters) values
	(unix_to_numeric('400'), 1,5,2,'item_name','symbol',now(),'{}');

END $$;

CREATE
  OR REPLACE FUNCTION get_user_perrmssions_for_object (
  userid INT
  ,objectid INT
  )
RETURNS setof VARCHAR AS $$

DECLARE usergroups INT;
DECLARE groupsroot INT;
DECLARE permissions_owner_read INT;
DECLARE permissions_owner_write INT;
DECLARE permissions_owner_delete INT;
DECLARE permissions_group_read INT;
DECLARE permissions_group_write INT;
DECLARE permissions_group_delete INT;
DECLARE permissions_other_read INT;
DECLARE permissions_other_write INT;
DECLARE permissions_other_delete INT;
DECLARE tablename VARCHAR(255);

BEGIN
  SELECT c_group
  FROM users
  WHERE c_uid = userid
  INTO usergroups;

  SELECT tableoid::regclass::TEXT
  FROM t_acl
  WHERE c_uid = objectid
  INTO tablename;
  
  groupsroot := 1;
  permissions_owner_read := 256;
  permissions_owner_write := 128;
  permissions_owner_delete:= 64;
  permissions_group_read:= 32;
  permissions_group_write:= 16;
  permissions_group_delete:= 8;
  permissions_other_read:= 4;
  permissions_other_write:= 2;
  permissions_other_delete:= 1;

  return query 
      SELECT DISTINCT ac.c_title
      FROM t_action AS ac
      INNER JOIN t_acl AS obj ON obj.c_uid = objectid
      INNER JOIN t_implemented_action AS ia ON ia.c_action = ac.c_title
        AND ia.c_table = tablename::TEXT
        AND ( (ia.c_status = 0) OR (ia.c_status & obj.c_status <> 0) )
      LEFT JOIN t_privilege AS pr ON pr.c_related_table = c_table
        AND pr.c_action = ac.c_title
        AND (( pr.c_type = 'object' AND pr.c_related_uid = objectid ) OR pr.c_type = 'global' OR ( pr.c_role = 'self' AND userid = objectid AND tablename = 'users' ))
        WHERE ac.c_apply_object
        AND (
        (usergroups & groupsroot <> 0)
        OR ( ac.c_title = 'read'   AND ((obj.c_unixperms & permissions_other_read <> 0)  OR ((obj.c_unixperms & permissions_owner_read <> 0)  AND obj.c_owner = userid ) OR ((obj.c_unixperms & permissions_group_read <> 0)  AND (usergroups & obj.c_group <> 0))))
        OR ( ac.c_title = 'write'  AND ((obj.c_unixperms & permissions_other_write <> 0) OR ((obj.c_unixperms & permissions_owner_write <> 0) AND obj.c_owner = userid ) OR ((obj.c_unixperms & permissions_group_write <> 0) AND (usergroups & obj.c_group <> 0))))
        OR ( ac.c_title = 'delete' AND ((obj.c_unixperms & permissions_other_delete <> 0)OR ((obj.c_unixperms & permissions_owner_delete <> 0)AND obj.c_owner = userid ) OR ((obj.c_unixperms & permissions_group_delete <> 0)AND (usergroups & obj.c_group <> 0))))
        OR ( pr.c_role = 'user'        AND pr.c_who = userid )
        OR ( pr.c_role = 'owner'       AND obj.c_owner = userid )
        OR ( pr.c_role = 'owner_group' AND (obj.c_group & usergroups <> 0))
        OR ( pr.c_role = 'group'       AND (pr.c_who & usergroups <> 0))
        )
        OR pr.c_role = 'self';
END $$
LANGUAGE plpgsql;

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

-- insert usefool data into dataase

DO
$$
DECLARE lastid int;

BEGIN

END $$;
