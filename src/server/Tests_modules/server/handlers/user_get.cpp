#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <sqlpp11/sqlpp11.h>
#include "database/UserHelper.hpp"

#include "TestCommon.hpp"

static constexpr schema::t_users u;

using namespace eedb;
using namespace test;

class GetUserTest : public ::testing::Test
{
public:

protected:
    eedb::db::UserHelper helper;

    DB db;
};


TEST_F( GetUserTest, getRootUserData ){
    ASSERT_FALSE(helper.getAllUserDataWhere(db, u.c_name == "fake"));
}

TEST_F(GetUserTest, getTrueUser ){
    auto userData = helper.getAllUserDataWhere(db, u.c_name == "ROOT" );

    ASSERT_TRUE(userData);
    EXPECT_EQ(userData->name, "ROOT");
}


TEST_F(GetUserTest, checkIfExists ){
    auto exists = helper.exists(db, u.c_name == "ROOT" );

    ASSERT_TRUE(exists);
}
