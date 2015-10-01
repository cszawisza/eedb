#include "gtest/gtest.h"
#include "utils/hash_passwd.h"

#include "core/auth/acl.hpp"


using namespace auth;
using namespace schema;

class ACL_test : public testing::Test
{
public:
    ACL_test(){

        schema::t_users u;
        schema::t_acl acl;
        bool error = false;

        db.start_transaction();

        //create test user
        m_uid = db(sqlpp::postgresql::insert_into(u)
           .set(u.c_group = 2,
                u.c_name = "test_user_x",
                u.c_email = "test_email_x@xx.xx",
                u.c_password = "passwd",
                u.c_salt = "salt"
                ).returning(u.c_uid) ).front().c_uid;

        m_root_obj = db(sqlpp::postgresql::insert_into(acl)
           .set( acl.c_owner = 1,
                 acl.c_group = 4,
                 acl.c_unixperms = 416  // 640  rw-r-----
                ).returning(acl.c_uid )).front().c_uid ;

        m_user_obj = db(sqlpp::postgresql::insert_into(acl)
           .set( acl.c_owner = m_uid,
                 acl.c_group = 4,
                 acl.c_unixperms = 416  // 640 rw-r-----
                ).returning(acl.c_uid )).front().c_uid;

        m_common_group = db(sqlpp::postgresql::insert_into(acl)
           .set( acl.c_owner = 1, // root as owner
                 acl.c_group = 2, // user group
                 acl.c_unixperms = 496  // 740 rwdrw----
                ).returning(acl.c_uid )).front().c_uid;

        m_other = db(sqlpp::postgresql::insert_into(acl)
           .set( acl.c_owner = 1, // root as owner
                 acl.c_group = 4, // not user group
                 acl.c_unixperms = 4  // 644 ------r--
                ).returning(acl.c_uid )).front().c_uid;
    }

    ~ACL_test(){
        db.rollback_transaction(false);
    }

    DB db;

    uint64_t m_uid;
    uint64_t m_root_obj, m_user_obj, m_common_group, m_other;
};

TEST_F(ACL_test, simple_permissions ){
    AccesControl acl(m_uid);

    // can't do anything with root's object
    EXPECT_FALSE( acl.checkUserAction<t_acl>(db, "read"  , m_root_obj) );
    EXPECT_FALSE( acl.checkUserAction<t_acl>(db, "write" , m_root_obj) );
    EXPECT_FALSE( acl.checkUserAction<t_acl>(db, "delete", m_root_obj) );

    // can read and write if in group
    EXPECT_TRUE ( acl.checkUserAction<t_acl>(db,"read"  , m_common_group) );
    EXPECT_TRUE ( acl.checkUserAction<t_acl>(db,"write" , m_common_group) );
    EXPECT_FALSE( acl.checkUserAction<t_acl>(db,"delete", m_common_group) );

    EXPECT_TRUE ( acl.checkUserAction<t_acl>(db,"read"  , m_user_obj) );
    EXPECT_TRUE ( acl.checkUserAction<t_acl>(db,"write" , m_user_obj) );
    EXPECT_FALSE( acl.checkUserAction<t_acl>(db,"delete", m_user_obj) );

    EXPECT_TRUE ( acl.checkUserAction<t_acl>(db,"read"  , m_other) );
    EXPECT_FALSE( acl.checkUserAction<t_acl>(db,"write" , m_other) );
    EXPECT_FALSE( acl.checkUserAction<t_acl>(db,"delete", m_other) );
}

TEST_F(ACL_test, root_can_everything ){
    AccesControl acl(1);

    // can't do anything with root's object
    EXPECT_TRUE ( acl.checkUserAction<t_acl>(db,"read"  , m_root_obj) );
    EXPECT_TRUE ( acl.checkUserAction<t_acl>(db,"write" , m_root_obj) );
    EXPECT_TRUE ( acl.checkUserAction<t_acl>(db,"delete", m_root_obj) );

    // can read and write if in group
    EXPECT_TRUE ( acl.checkUserAction<t_acl>(db,"read"  , m_common_group) );
    EXPECT_TRUE ( acl.checkUserAction<t_acl>(db,"write" , m_common_group) );
    EXPECT_TRUE ( acl.checkUserAction<t_acl>(db,"delete", m_common_group) );

    EXPECT_TRUE ( acl.checkUserAction<t_acl>(db,"read"  , m_user_obj) );
    EXPECT_TRUE ( acl.checkUserAction<t_acl>(db,"write" , m_user_obj) );
    EXPECT_TRUE ( acl.checkUserAction<t_acl>(db,"delete", m_user_obj) );

    EXPECT_TRUE ( acl.checkUserAction<t_acl>(db,"read"  , m_other) );
    EXPECT_TRUE ( acl.checkUserAction<t_acl>(db,"write" , m_other) );
    EXPECT_TRUE ( acl.checkUserAction<t_acl>(db,"delete", m_other) );
}

TEST_F(ACL_test, table_acl){
    AccesControl acl(m_uid);

    EXPECT_FALSE( acl.checkUserAction<t_users>(db,"read") );
    EXPECT_FALSE( acl.checkUserAction<t_acl>(db,"write") );
}
