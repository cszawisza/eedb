#include "gtest/gtest.h"

#include <core/category.hpp>

#include <sqlpp11/sqlpp11.h>

#include <core/database/idatabase.h>
#include <core/database/AclHelper.hpp>
#include <core/database/InventoryHelper.hpp>

#include <sql_schema/t_shelfs.h>
#include <sql_schema/t_categories.h>

#include "TestCommon.hpp"

using namespace eedb::db;
using namespace test;

class CategoriesTest : public ::testing::Test
{
public:
    CategoriesTest(){
        db.start_transaction();
    }

    ~CategoriesTest(){
        db.rollback_transaction(false);
    }

    DB db;
    eedb::handlers::Category categoryHandler;
};

TEST_F(CategoriesTest, simpleAdd){
}
