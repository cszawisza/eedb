#include "gtest/gtest.h"
#include "utils/hash_passwd.h"
#include "../../common.h"

#include "core/acl.h"


using namespace auth;

class AccesControl_test : public testing::Test
{
public:
    AccesControl_test(){
        DB db;

        schema::t_users u;
        schema::t_acl acl;
        bool error = false;
        try{
            db.start_transaction();
            createBackup(db, u);
            createBackup(db, acl);
        }
        catch( sqlpp::exception ){
            error = true;
        }

        if(error)
            db.rollback_transaction(false);
        else
            db.commit_transaction();


        //create test user
        db(insert_into(u)
           .set(u.c_group = 2,
                u.c_name = "test_user_x",
                u.c_email = "test_email_x@xx.xx",
                u.c_password = "passwd",
                u.c_salt = "salt"
                ));

        m_uid = db(sqlpp::select(u.c_uid).from(u).where(u.c_name == "test_user_x")).front().c_uid;

        db(insert_into(acl)
           .set( acl.c_owner = 1,
                 acl.c_group = 4,
                 acl.c_unixperms = 416  // 640  rw-r-----
                ));
        m_root_obj = m_uid +1;

        db(insert_into(acl)
           .set( acl.c_owner = m_uid,
                 acl.c_group = 4,
                 acl.c_unixperms = 416  // 640 rw-r-----
                ));
        m_user_obj = m_uid +2;

        db(insert_into(acl)
           .set( acl.c_owner = 1, // root as owner
                 acl.c_group = 2, // user group
                 acl.c_unixperms = 496  // 740 rwdrw----
                ));
        m_common_group = m_uid +3;

        db(insert_into(acl)
           .set( acl.c_owner = 1, // root as owner
                 acl.c_group = 4, // not user group
                 acl.c_unixperms = 4  // 644 ------r--
                ));
        m_other = m_uid +4;

    }

    ~AccesControl_test(){
        schema::t_users u;
        schema::t_acl acl;
        DB db;
        restoreBackup(db,u);
        restoreBackup(db,acl);
    }

    quint64 m_uid;
    quint64 m_root_obj, m_user_obj, m_common_group, m_other;
};

TEST_F(AccesControl_test, simple_permissions ){
    AccesControl acl(m_uid);
    schema::t_acl a;

    // can't do anything with root's object
    EXPECT_FALSE( acl.checkUserAction("read"  , a, m_root_obj) );
    EXPECT_FALSE( acl.checkUserAction("write" , a, m_root_obj) );
    EXPECT_FALSE( acl.checkUserAction("delete", a, m_root_obj) );

    // can read and write if in group
    EXPECT_TRUE ( acl.checkUserAction("read"  , a, m_common_group) );
    EXPECT_TRUE ( acl.checkUserAction("write" , a, m_common_group) );
    EXPECT_FALSE( acl.checkUserAction("delete", a, m_common_group) );

    EXPECT_TRUE ( acl.checkUserAction("read"  , a, m_user_obj) );
    EXPECT_TRUE ( acl.checkUserAction("write" , a, m_user_obj) );
    EXPECT_FALSE( acl.checkUserAction("delete", a, m_user_obj) );

    EXPECT_TRUE ( acl.checkUserAction("read"  , a, m_other) );
    EXPECT_FALSE( acl.checkUserAction("write" , a, m_other) );
    EXPECT_FALSE( acl.checkUserAction("delete", a, m_other) );
}

TEST_F(AccesControl_test, root_can_everything ){
    AccesControl acl(1);
    schema::t_acl a;

    // can't do anything with root's object
    EXPECT_TRUE ( acl.checkUserAction("read"  , a, m_root_obj) );
    EXPECT_TRUE ( acl.checkUserAction("write" , a, m_root_obj) );
    EXPECT_TRUE ( acl.checkUserAction("delete", a, m_root_obj) );

    // can read and write if in group
    EXPECT_TRUE ( acl.checkUserAction("read"  , a, m_common_group) );
    EXPECT_TRUE ( acl.checkUserAction("write" , a, m_common_group) );
    EXPECT_TRUE ( acl.checkUserAction("delete", a, m_common_group) );

    EXPECT_TRUE ( acl.checkUserAction("read"  , a, m_user_obj) );
    EXPECT_TRUE ( acl.checkUserAction("write" , a, m_user_obj) );
    EXPECT_TRUE ( acl.checkUserAction("delete", a, m_user_obj) );

    EXPECT_TRUE ( acl.checkUserAction("read"  , a, m_other) );
    EXPECT_TRUE ( acl.checkUserAction("write" , a, m_other) );
    EXPECT_TRUE ( acl.checkUserAction("delete", a, m_other) );
}

TEST_F(AccesControl_test, table_acl){
    AccesControl acl(m_uid);
    schema::t_users u;
    schema::t_acl a;

    EXPECT_FALSE( acl.checkUserAction("read", u) );
    EXPECT_FALSE( acl.checkUserAction("write", a) );
}
