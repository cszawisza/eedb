#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <sqlpp11/sqlpp11.h>
#include "database/UserHelper.hpp"

#include "TestCommon.hpp"

static constexpr schema::t_acl a;
static constexpr schema::t_users u;
static constexpr schema::t_inventories i;
static constexpr schema::t_files f;

using namespace eedb;
using namespace test;
using eedb::db::AclHelper;



class UserHelperSelectTest : public ::testing::Test
{
public:
    UserHelperSelectTest()
    {
        db.start_transaction();
    }

    ~UserHelperSelectTest(){
        db.rollback_transaction(false);
    }

protected:
    DB db;
    AclHelper helper;
    pb::Acl dataToInsert;
};

TEST_F(UserHelperSelectTest, executeSelectFromDifferentTables ){
    EXPECT_TRUE( db(helper.selectAcl( a.c_uid == 0 ) ).empty() );
    EXPECT_TRUE( db(helper.selectAclFrom<schema::t_files>( f.c_size == 0 and f.c_sha == "x" ) ).empty() );
    EXPECT_TRUE( db(helper.selectAclFrom<schema::t_inventories>( i.c_name == "unknown inventory") ).empty() );
    EXPECT_TRUE( db(helper.selectAclFrom<schema::t_users>( u.c_phonenumber == "0700 123 123" or u.c_name.like("PIMP"))).empty() );
}

TEST_F(UserHelperSelectTest, selectSomethinfFromTables ){
    EXPECT_FALSE( db(helper.selectAcl( true ) ).empty() );
    EXPECT_FALSE( db(helper.selectAclFrom<schema::t_users>( true )).empty() );
}

TEST_F(UserHelperSelectTest, notFoundAcl ){
    EXPECT_FALSE( helper.getAcl(db, 0) );
}

TEST_F(UserHelperSelectTest,  ){
    EXPECT_TRUE( helper.getAcl(db, 1) );
}
