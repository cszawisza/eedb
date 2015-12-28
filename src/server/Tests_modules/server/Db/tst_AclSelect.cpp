#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <sqlpp11/sqlpp11.h>
#include "database/UserHelper.hpp"

#include "TestCommon.hpp"

static constexpr schema::stat a;
static constexpr schema::users u;
static constexpr schema::inventories i;
static constexpr schema::files f;

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
    protobuf::Acl dataToInsert;
};

TEST_F(UserHelperSelectTest, executeSelectFromDifferentTables ){
    EXPECT_TRUE( db(helper.selectAcl( a.uid == 0 ) ).empty() );
    EXPECT_TRUE( db(helper.selectAclFrom<schema::files>( f.file_size == 0 and f.file_hash == "x" ) ).empty() );
    EXPECT_TRUE( db(helper.selectAclFrom<schema::inventories>( i.name == "unknown inventory") ).empty() );
    EXPECT_TRUE( db(helper.selectAclFrom<schema::users>( u.phonenumber == "0700 123 123" or u.name.like("PIMP"))).empty() );
}

TEST_F(UserHelperSelectTest, selectSomethinfFromTables ){
    EXPECT_FALSE( db(helper.selectAcl( true ) ).empty() );
    EXPECT_FALSE( db(helper.selectAclFrom<schema::users>( true )).empty() );
}

TEST_F(UserHelperSelectTest, notFoundAcl ){
    EXPECT_FALSE( helper.getAcl(db, 0) );
}

TEST_F(UserHelperSelectTest,  ){
    EXPECT_TRUE( helper.getAcl(db, 1) );
}
