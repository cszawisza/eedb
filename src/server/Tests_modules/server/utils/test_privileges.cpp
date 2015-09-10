#include <gtest/gtest.h>

#include "sql_schema/t_acl.h"
#include "sql_schema/t_files.h"
#include "sql_schema/t_users.h"

#include "core/database/idatabase.h"
#include "core/auth/action.hpp"
#include "core/auth/implementedaction.hpp"
#include "core/auth/privilege.hpp"
#include "core/auth/acl.hpp"

using namespace auth;

class PrivilegesTest : public testing::Test
{
public:
    PrivilegesTest(){
        db.start_transaction();

        m_uid = addDummyUser("test_new_user");
        m_uid2= addDummyUser("test_new_user2");
        addDummyFile();
    }

    ~PrivilegesTest(){
        db.rollback_transaction(false);
    }

    DB db;

//    c_name      TEXT    NOT NULL CHECK(length(c_name) < 4096 ),
//    c_size      BIGINT  NOT NULL,
//    c_sha       TEXT    NOT NULL CHECK(length(c_sha) < 512 ),
//    c_mimetype  TEXT    NOT NULL CHECK(length(c_mimetype) < 256 ),
    void addDummyFile(){
        static constexpr schema::t_files f;

        // user cant read this file with normal unixperms
        // must have a special permision
        db(insert_into(f)
                .set(
                    f.c_group = 1<<31, // user not in this group
                    f.c_unixperms =  448, // 700
                    f.c_owner =  1, // owner root
                    f.c_status = 0 ,
                    f.c_name = "test_new_file",
                    f.c_size = 1000,
                    f.c_sha = "xxxxxxxxxxxxxxxxxx",
                    f.c_mimetype = "some mime type"
                ));

        m_fid = db.lastInsertId(tableName<schema::t_acl>(), "c_uid");
    }

    uint64_t addDummyUser( string name ){
        static constexpr schema::t_users u;

        db(insert_into(u)
                .set(
                    u.c_group = 2, // default to user group
                    u.c_unixperms =  484,
                    u.c_owner =  1,
                    u.c_status = 0 ,
                    u.c_name = name ,
                    u.c_email = name + "@email.com",
                    u.c_password = "passwd",
                    u.c_salt = "salt"
                ));

        return db.lastInsertId(tableName<schema::t_acl>(), "c_uid");
    }
    schema::t_files f;
    uint64_t m_uid, m_uid2, m_fid;
};


TEST_F(PrivilegesTest, roleNameConversion){
    Role role;

    EXPECT_EQ( "owner"         , role.name(auth::Role_Owner ));
    EXPECT_EQ( "user"          , role.name(auth::Role_User  ));
    EXPECT_EQ( auth::Role_Owner, role.id("owner")           );
    EXPECT_EQ( auth::Role_User , role.id("user")            );
}

TEST_F(PrivilegesTest, typeNameConversion){
    Type role;

    EXPECT_EQ( "global"         , role.name(auth::Type_Global ));
    EXPECT_EQ( auth::Type_Object, role.id("object")            );
}

TEST_F(PrivilegesTest, checkIfExists){
    Privilege priv;
    priv.giveUser( 0 ).privilegeFor("modify").forTable(f);
    EXPECT_FALSE(priv.exists(db));
}

TEST_F(PrivilegesTest, addPrivilegeForObjectToUser){
    Privilege priv;

    AccesControl acl1(m_uid);
    AccesControl acl2(m_uid2);
    Action a("remove_file", Object );
    ImplementedAction ia( "remove_file", State_Normal, sqlpp::tableName<schema::t_files>() );

    priv.giveUser(m_uid).privilegeFor("remove_file").onObject(m_fid).inTable(f);

    EXPECT_FALSE(acl1.checkUserAction<schema::t_files>(db, "remove_file", m_fid));
    EXPECT_FALSE(acl2.checkUserAction<schema::t_files>(db, "remove_file", m_fid));

    EXPECT_NO_THROW( priv.force_save(db) );
    EXPECT_TRUE( a.exists(db) );
    EXPECT_TRUE( ia.exists(db) );
    EXPECT_TRUE( priv.exists(db) );

    EXPECT_TRUE( acl1.checkUserAction<schema::t_files>(db, "remove_file", m_fid) );
    EXPECT_FALSE(acl2.checkUserAction<schema::t_files>(db, "remove_file", m_fid));
}

TEST_F(PrivilegesTest, addPrivilegeForObjectToGroup){
    Privilege priv;
    AccesControl acl1(m_uid);
    AccesControl acl2(m_uid2);
    Action a("remove_file", Object );
    ImplementedAction ia( "remove_file", State_Normal, sqlpp::tableName<schema::t_files>() );

    priv.giveGroup( 2 ).privilegeFor( "remove_file" ).onObject( m_fid ).inTable(f);

    EXPECT_FALSE(acl1.checkUserAction<schema::t_files>(db, "remove_file", m_fid));
    EXPECT_FALSE(acl2.checkUserAction<schema::t_files>(db, "remove_file", m_fid));

    EXPECT_NO_THROW( priv.force_save(db) );
    EXPECT_TRUE( a.exists(db) );
    EXPECT_TRUE( ia.exists(db) );
    EXPECT_TRUE( priv.exists(db) );

    EXPECT_TRUE( acl1.checkUserAction<schema::t_files>(db, "remove_file", m_fid) );
    EXPECT_TRUE( acl2.checkUserAction<schema::t_files>(db, "remove_file", m_fid));
}

TEST_F(PrivilegesTest, privilegeBuilder){
    Privilege priv;
    AccesControl acl1(m_uid);

    priv.giveGroup( 2 ).privilegeFor("remove_file").forTable(f);
    priv.force_save(db);

    EXPECT_TRUE( acl1.checkUserAction<schema::t_files>(db, "remove_file") );
}

TEST_F(PrivilegesTest, differentStates){
    Privilege priv;
    AccesControl acl1(m_uid);

    EXPECT_FALSE( acl1.checkUserAction<schema::t_files>(db, "remove_file", m_fid) );

    priv.giveUser( m_uid ).privilegeFor("remove_file").onObject( m_fid ).inTable(f).inState( State_Deleted ).force_save(db);

    EXPECT_FALSE( acl1.checkUserAction<schema::t_files>(db, "remove_file", m_fid) );

    db(update(f).set(f.c_status = (int)State_Deleted).where(f.c_uid == m_fid) );

    EXPECT_TRUE( acl1.checkUserAction<schema::t_files>(db, "remove_file", m_fid) );
}

TEST_F(PrivilegesTest, differentStatesToDeleted){
    Privilege priv;
    AccesControl acl1(m_uid);

    EXPECT_FALSE( acl1.checkUserAction<schema::t_files>(db, "remove_file", m_fid) );

    priv.giveUser( m_uid ).privilegeFor("remove_file").onObject( m_fid ).inTable(f).inState( State_BeingModified ).force_save(db);
    db(update(f).set(f.c_status = (int)State_BeingModified).where(f.c_uid == m_fid) );
    EXPECT_TRUE( acl1.checkUserAction<schema::t_files>(db, "remove_file", m_fid) );

    db(update(f).set(f.c_status = (int)State_Deleted).where(f.c_uid == m_fid) );

    EXPECT_FALSE( acl1.checkUserAction<schema::t_files>(db, "remove_file", m_fid) );
}
