#include "gtest/gtest.h"
#include "utils/hash_passwd.h"
#include "../../common.h"

#include "core/acl.h"


using namespace auth;

class AccesControl_test : public testing::Test
{
public:
    AccesControl_test(){
        createBackup("t_acl");
        createBackup("t_users");

        DB db;
        schema::t_users u;
        schema::t_acl acl;

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
        restoreBackup("t_acl");
        restoreBackup("t_users");
    }

    quint64 m_uid;
    quint64 m_root_obj, m_user_obj, m_common_group, m_other;
};

TEST_F(AccesControl_test, simple_permissions ){
    AccesControl acl(m_uid);

    // can't do anything with root's object
    EXPECT_FALSE( acl.checkUserAction("read"  , m_root_obj, "t_acl") );
    EXPECT_FALSE( acl.checkUserAction("write" , m_root_obj, "t_acl") );
    EXPECT_FALSE( acl.checkUserAction("delete", m_root_obj, "t_acl") );

    // can read and write if in group
    EXPECT_TRUE ( acl.checkUserAction("read"  , m_common_group, "t_acl") );
    EXPECT_TRUE ( acl.checkUserAction("write" , m_common_group, "t_acl") );
    EXPECT_FALSE( acl.checkUserAction("delete", m_common_group, "t_acl") );

    EXPECT_TRUE ( acl.checkUserAction("read"  , m_user_obj, "t_acl") );
    EXPECT_TRUE ( acl.checkUserAction("write" , m_user_obj, "t_acl") );
    EXPECT_FALSE( acl.checkUserAction("delete", m_user_obj, "t_acl") );

    EXPECT_TRUE ( acl.checkUserAction("read"  , m_other, "t_acl") );
    EXPECT_FALSE( acl.checkUserAction("write" , m_other, "t_acl") );
    EXPECT_FALSE( acl.checkUserAction("delete", m_other, "t_acl") );
}

TEST_F(AccesControl_test, root_can_everything ){
    AccesControl acl(1);

    // can't do anything with root's object
    EXPECT_TRUE ( acl.checkUserAction("read"  , m_root_obj, "t_acl") );
    EXPECT_TRUE ( acl.checkUserAction("write" , m_root_obj, "t_acl") );
    EXPECT_TRUE ( acl.checkUserAction("delete", m_root_obj, "t_acl") );

    // can read and write if in group
    EXPECT_TRUE ( acl.checkUserAction("read"  , m_common_group, "t_acl") );
    EXPECT_TRUE ( acl.checkUserAction("write" , m_common_group, "t_acl") );
    EXPECT_TRUE ( acl.checkUserAction("delete", m_common_group, "t_acl") );

    EXPECT_TRUE ( acl.checkUserAction("read"  , m_user_obj, "t_acl") );
    EXPECT_TRUE ( acl.checkUserAction("write" , m_user_obj, "t_acl") );
    EXPECT_TRUE ( acl.checkUserAction("delete", m_user_obj, "t_acl") );

    EXPECT_TRUE ( acl.checkUserAction("read"  , m_other, "t_acl") );
    EXPECT_TRUE ( acl.checkUserAction("write" , m_other, "t_acl") );
    EXPECT_TRUE ( acl.checkUserAction("delete", m_other, "t_acl") );
}
