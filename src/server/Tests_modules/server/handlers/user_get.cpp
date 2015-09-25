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
    auto e = db.prepare( helper.selectExists( u.c_name == parameter(u.c_name) ) );
    e.params.c_name = "ROOT";

    EXPECT_TRUE(db(e).front().exists);
}

//constexpr schema::t_users u;
//auto prep = db.prepare(sqlpp::select(u.c_uid).from(u)
//                       .where( u.c_name == parameter(u.c_name) ));
//prep.params.c_name = name;
//auto res = db(prep);

//optional<int64_t> id;
//if(!res.empty())
//    id = res.front().c_uid;
//return id;


//TEST_F(GetUserTest, prep){
//    constexpr schema::t_users u;
//    auto preparedStatement = getUserPrep(db, u.c_name == parameter(u.c_name) );
//    preparedStatement.params.c_name = "CYCEK";
//}
