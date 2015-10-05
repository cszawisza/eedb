#include "gtest/gtest.h"
#include "utils/hash_passwd.h"

#include "core/auth/acl.hpp"


using namespace auth;
using namespace schema;

class ACL_test : public testing::Test
{
public:
    ACL_test(){

        schema::users u;
        schema::stat stat;
        bool error = false;

        db.start_transaction();

        //create test user
        m_uid = db(sqlpp::postgresql::insert_into(u)
           .set(u.stat_group = 2,
                u.name = "test_user_x",
                u.email = "test_email_x@xx.xx",
                u.password = "passwd",
                u.salt = "salt"
                ).returning(u.uid) ).front().uid;

        m_root_obj = db(sqlpp::postgresql::insert_into(stat)
           .set( stat.owner = 1,
                 stat.stat_group = 4,
                 stat.unixperms = 416,  // 640  rw-r-----
                 stat.name = "obj"
                ).returning(stat.uid )).front().uid ;

        m_user_obj = db(sqlpp::postgresql::insert_into(stat)
           .set( stat.owner = m_uid,
                 stat.stat_group = 4,
                 stat.unixperms = 416,  // 640 rw-r-----
                 stat.name = "obj"
                ).returning(stat.uid )).front().uid;

        m_common_group = db(sqlpp::postgresql::insert_into(stat)
           .set( stat.owner = 1, // root as owner
                 stat.stat_group = 2, // user group
                 stat.unixperms = 496,  // 740 rwdrw----
                 stat.name = "obj"
                ).returning(stat.uid )).front().uid;

        m_other = db(sqlpp::postgresql::insert_into(stat)
           .set( stat.owner = 1, // root as owner
                 stat.stat_group = 4, // not user group
                 stat.unixperms = 4,  // 644 ------r--
                 stat.name = "obj"
                ).returning(stat.uid )).front().uid;
    }

    ~ACL_test(){
        db.rollback_transaction(false);
    }

    DB db;

    uint64_t m_uid;
    uint64_t m_root_obj, m_user_obj, m_common_group, m_other;
};

TEST_F(ACL_test, simple_permissions ){
    AccesControl stat(m_uid);

    // can't do anything with root's object
    EXPECT_FALSE( stat.checkUserAction<schema::stat>(db, "read"  , m_root_obj) );
    EXPECT_FALSE( stat.checkUserAction<schema::stat>(db, "write" , m_root_obj) );
    EXPECT_FALSE( stat.checkUserAction<schema::stat>(db, "delete", m_root_obj) );

    // can read and write if in group
    EXPECT_TRUE ( stat.checkUserAction<schema::stat>(db,"read"  , m_common_group) );
    EXPECT_TRUE ( stat.checkUserAction<schema::stat>(db,"write" , m_common_group) );
    EXPECT_FALSE( stat.checkUserAction<schema::stat>(db,"delete", m_common_group) );

    EXPECT_TRUE ( stat.checkUserAction<schema::stat>(db,"read"  , m_user_obj) );
    EXPECT_TRUE ( stat.checkUserAction<schema::stat>(db,"write" , m_user_obj) );
    EXPECT_FALSE( stat.checkUserAction<schema::stat>(db,"delete", m_user_obj) );

    EXPECT_TRUE ( stat.checkUserAction<schema::stat>(db,"read"  , m_other) );
    EXPECT_FALSE( stat.checkUserAction<schema::stat>(db,"write" , m_other) );
    EXPECT_FALSE( stat.checkUserAction<schema::stat>(db,"delete", m_other) );
}

TEST_F(ACL_test, root_can_everything ){
    AccesControl stat(1);

    // can't do anything with root's object
    EXPECT_TRUE ( stat.checkUserAction<schema::stat>(db,"read"  , m_root_obj) );
    EXPECT_TRUE ( stat.checkUserAction<schema::stat>(db,"write" , m_root_obj) );
    EXPECT_TRUE ( stat.checkUserAction<schema::stat>(db,"delete", m_root_obj) );

    // can read and write if in group
    EXPECT_TRUE ( stat.checkUserAction<schema::stat>(db,"read"  , m_common_group) );
    EXPECT_TRUE ( stat.checkUserAction<schema::stat>(db,"write" , m_common_group) );
    EXPECT_TRUE ( stat.checkUserAction<schema::stat>(db,"delete", m_common_group) );

    EXPECT_TRUE ( stat.checkUserAction<schema::stat>(db,"read"  , m_user_obj) );
    EXPECT_TRUE ( stat.checkUserAction<schema::stat>(db,"write" , m_user_obj) );
    EXPECT_TRUE ( stat.checkUserAction<schema::stat>(db,"delete", m_user_obj) );

    EXPECT_TRUE ( stat.checkUserAction<schema::stat>(db,"read"  , m_other) );
    EXPECT_TRUE ( stat.checkUserAction<schema::stat>(db,"write" , m_other) );
    EXPECT_TRUE ( stat.checkUserAction<schema::stat>(db,"delete", m_other) );
}

TEST_F(ACL_test, table_stat){
    AccesControl stat(m_uid);

    EXPECT_FALSE( stat.checkUserAction<users>(db,"read") );
    EXPECT_FALSE( stat.checkUserAction<schema::stat>(db,"write") );
}
