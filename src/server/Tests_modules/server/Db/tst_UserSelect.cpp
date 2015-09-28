#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <sqlpp11/sqlpp11.h>
#include "database/UserHelper.hpp"

#include "TestCommon.hpp"

static constexpr schema::t_users u;

using namespace eedb;
using namespace test;

class UserHelperTest : public ::testing::Test
{
public:

protected:
    eedb::db::UserHelper helper;

    DB db;
};

TEST_F(UserHelperTest, getTrueUser ){
    auto userData = db( helper.selectAll( u.c_name == "ROOT" ) );
    EXPECT_EQ(userData.front().c_name, "ROOT");
}

TEST_F(UserHelperTest, checkIfExists ){
    auto e = db.prepare( helper.selectExists( u.c_name == parameter(u.c_name) ) );

    e.params.c_name = "ROOT";
    EXPECT_TRUE(db(e).front().exists );

    e.params.c_name = "fake";
    EXPECT_FALSE(db(e).front().exists );
}

//TEST_F(UserHelperTest, getUserData ){

//}

TEST_F(UserHelperTest, prep){
    constexpr schema::t_users u;
    auto preparedStatement = db.prepare( helper.selectExists(u.c_name == parameter(u.c_name)) );

    preparedStatement.params.c_name = "CYCEK";
}
