#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <sqlpp11/sqlpp11.h>
#include "database/CategoryHelper.hpp"

#include "TestCommon.hpp"

static constexpr schema::users u;

using namespace eedb;
using namespace test;
using eedb::db::CategoryHelper;

class CategoryDbLayerInserttest : public ::testing::Test
{
public:
    CategoryDbLayerInserttest()
    {
        db.start_transaction();
    }

    ~CategoryDbLayerInserttest(){
        db.rollback_transaction(false);
    }

protected:
    DB db;
    CategoryHelper helper;
    protobuf::CategoryReq dataToInsert;
};


//TEST_F(CategoryDbLayerInserttest, insert ){
//    EXPECT_NO_THROW(db( helper.insert() ) );
//}
