#include <gtest/gtest.h>

#include "sql_schema/acl.h"
#include "sql_schema/t_files.h"
#include "sql_schema/users.h"

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
    void addDummyFile(){
        static constexpr schema::t_files f;

        // user cant read this file with normal unixperms
        // must have a special permision
        db(sqlpp::postgresql::insert_into(f)
                .set(
                    f.acl_group = 1<<31, // user not in this group
                    f.unixperms =  448, // 700
                    f.owner =  1, // owner root
                    f.status = 0 ,
                    f.name = "test_new_file",
                    f.c_size = 1000,
                    f.c_sha = "xxxxxxxxxxxxxxxxxx",
                    f.c_mimetype = "some mime type"
                ));

        m_fid = db.lastInsertId(tableName<schema::acl>(), "uid"); ///TODO chenge to automatic generation
    }

    uint64_t addDummyUser( string name ){
        static constexpr schema::users u;

        db(sqlpp::postgresql::insert_into(u)
                .set(
                    u.acl_group = 2, // default to user group
                    u.unixperms =  484,
                    u.owner =  1,
                    u.status = 0 ,
                    u.name = name ,
                    u.email = name + "@email.com",
                    u.password = "passwd",
                    u.salt = "salt"
                ));

        return db.lastInsertId(tableName<schema::acl>(), "uid"); ///TODO chenge to automatic generation
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

    db(update(f).set(f.status = (int)State_Deleted).where(f.uid == m_fid) );

    EXPECT_TRUE( acl1.checkUserAction<schema::t_files>(db, "remove_file", m_fid) );
}

TEST_F(PrivilegesTest, differentStatesToDeleted){
    Privilege priv;
    AccesControl acl1(m_uid);

    EXPECT_FALSE( acl1.checkUserAction<schema::t_files>(db, "remove_file", m_fid) );

    priv.giveUser( m_uid ).privilegeFor("remove_file").onObject( m_fid ).inTable(f).inState( State_BeingModified ).force_save(db);
    db(update(f).set(f.status = (int)State_BeingModified).where(f.uid == m_fid) );
    EXPECT_TRUE( acl1.checkUserAction<schema::t_files>(db, "remove_file", m_fid) );

    db(update(f).set(f.status = (int)State_Deleted).where(f.uid == m_fid) );

    EXPECT_FALSE( acl1.checkUserAction<schema::t_files>(db, "remove_file", m_fid) );
}
