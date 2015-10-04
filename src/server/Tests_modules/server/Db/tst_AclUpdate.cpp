#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <sqlpp11/sqlpp11.h>
#include "database/UserHelper.hpp"

#include "TestCommon.hpp"

static constexpr schema::t_users u;

using namespace eedb;
using namespace test;
using eedb::db::AclHelper;

class UserHelperInsertTest : public ::testing::Test
{
public:
    UserHelperInsertTest()
    {
        db.start_transaction();

        dataToInsert.set_uid(0);
        dataToInsert.set_group(0);
        dataToInsert.set_owner(0);
        dataToInsert.set_status(0);
        dataToInsert.set_unixperms(0);
    }

    ~UserHelperInsertTest(){
        db.rollback_transaction(false);
    }

protected:
    DB db;
    AclHelper helper;
    pb::Acl dataToInsert;
};

TEST_F(UserHelperInsertTest, updateAclEntry ){
    EXPECT_NE( 0, db(helper.selectAclFrom<schema::t_users>(u.c_name == "ROOT" ) ).front().c_owner );
    EXPECT_NE( 0, db(helper.selectAclFrom<schema::t_users>(u.c_name == "ROOT" ) ).front().c_group );
    EXPECT_NE( 0, db(helper.selectAclFrom<schema::t_users>(u.c_name == "ROOT" ) ).front().c_unixperms );
    EXPECT_NO_THROW(db(helper.updateWhere<schema::t_users>(dataToInsert, u.c_name == "ROOT" )) );
    EXPECT_EQ( 0, db(helper.selectAclFrom<schema::t_users>(u.c_name == "ROOT" ) ).front().c_owner );
    EXPECT_EQ( 0, db(helper.selectAclFrom<schema::t_users>(u.c_name == "ROOT" ) ).front().c_group );
    EXPECT_EQ( 0, db(helper.selectAclFrom<schema::t_users>(u.c_name == "ROOT" ) ).front().c_unixperms );
}

TEST_F(UserHelperInsertTest, expectFailWhenNoIdFound ){
    EXPECT_NO_THROW(db(helper.update(dataToInsert)) );
}