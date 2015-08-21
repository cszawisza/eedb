#include "gtest/gtest.h"

#include <core/inventory.hpp>

#include <sqlpp11/sqlpp11.h>
#include <core/database/idatabase.h>
#include <core/database/AclHelper.hpp>
#include <core/database/InventoryHelper.hpp>

#include <sql_schema/t_shelfs.h>

#include <memory>

#include "TestCommon.hpp"

using namespace eedb::db;
using namespace test;

class inventoryTest : public ::testing::Test
{
public:
    DB db;
};

TEST_F(inventoryTest, simpleAdd){

}
