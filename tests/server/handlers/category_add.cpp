#include "gtest/gtest.h"

#include <core/category.hpp>

#include <sqlpp11/sqlpp11.h>
#include <core/database/idatabase.h>
#include <core/database/AclHelper.hpp>
#include <core/database/InventoryHelper.hpp>

#include <sql_schema/t_shelfs.h>

#include "TestCommon.hpp"

using namespace eedb::db;
using namespace test;

//class CategoriesTest : public ::testing::Test
//{
//    CategoriesTest(){
//        db.start_transaction();
//    }
//    ~CategoriesTest(){
//        db.rollback_transaction(false);
//    }

//public:
//    DB db;
//    eedb::handlers::Category categoryHandler;
//};

//TEST_F(CategoriesTest, simpleAdd){
//    schema::t_categories cat;
//    db(select(all_of(cat)).where(cat.c_parent_category_id == 1 and cat.c_name == "name") );
//}
