#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <sqlpp11/sqlpp11.h>
#include "database/UserHelper.hpp"

#include "TestCommon.hpp"

static constexpr schema::t_users u;

using namespace eedb;
using namespace test;

class UserHelperTestInsert : public ::testing::Test
{
public:

protected:
    eedb::db::UserHelper helper;
    DB db;
};

TEST_F( UserHelperTestInsert, insert ){

}
