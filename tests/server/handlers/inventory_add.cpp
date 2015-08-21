#include "gtest/gtest.h"

#include <core/inventory.hpp>

#include <memory>

#include "TestCommon.hpp"

using namespace eedb::db;
using namespace test;

class inventoryTest : public ::testing::Test
{
public:
    schema::t_users u;
    schema::t_user_inventories ui;
    schema::t_inventories i;
    schema::t_shelfs sh;

    inventoryTest() {
        db.start_transaction();

        m_userId = addUser(db, "xxxxxxx");
        m_invId = addInventory(db, "new_inventory_testing", login(db, "xxxxxxx") );
    }

    ~inventoryTest(){
        db.rollback_transaction(false);
    }

    bool inventoryExists(const char * name){
        return eedb::db::InventoryHelper::getInventoryIdByName(db, name) > 0;
    }

    DB db;
    uint64_t m_userId= 0;
    uint64_t m_invId= 0;
};

TEST_F(inventoryTest, checkInventory){
    EXPECT_TRUE( inventoryExists("new_inventory_testing") );
}

TEST_F(inventoryTest, checkAcl){
    auto acl = AclHelper::getAcl(db, m_invId);
    EXPECT_EQ( m_userId, acl.owner() );
}

TEST_F(inventoryTest, userCanEditNewlyCreatedInventory ){
    auth::AccesControl acces(m_userId);
    auth::AccesControl other( addUser(db,"xxxxxxx2") );

    EXPECT_TRUE(acces.checkUserAction<schema::t_inventories>(db, "read", m_invId ) );
    EXPECT_TRUE(acces.checkUserAction<schema::t_inventories>(db, "write", m_invId ) );
    EXPECT_TRUE(acces.checkUserAction<schema::t_inventories>(db, "delete", m_invId ) );

    EXPECT_TRUE(other.checkUserAction<schema::t_inventories>(db, "read", m_invId ) );
    EXPECT_FALSE(other.checkUserAction<schema::t_inventories>(db, "write", m_invId ) );
    EXPECT_FALSE(other.checkUserAction<schema::t_inventories>(db, "delete", m_invId ) );
}

