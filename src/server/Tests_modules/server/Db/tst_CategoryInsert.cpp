#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <sqlpp11/sqlpp11.h>
#include "database/CategoryHelper.hpp"

#include "TestCommon.hpp"

static constexpr schema::users u;

using namespace eedb;
using namespace test;
using eedb::db::CategoryHelper;

class CategoryDbLayerInsertTest : public ::testing::Test
{
public:
    CategoryDbLayerInsertTest()
    {
        db.start_transaction();
    }

    ~CategoryDbLayerInsertTest(){
        db.rollback_transaction(false);
    }

protected:
    DB db;
    CategoryHelper helper;
    requests::category::IAdd* dataToInsert;
};


//TEST_F(CategoryDbLayerInserttest, insert ){
//    EXPECT_NO_THROW(db( helper.insert() ) );
//}
