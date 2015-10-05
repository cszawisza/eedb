#include "gtest/gtest.h"

#include <core/inventory.hpp>

#include <memory>

#include "TestCommon.hpp"

using namespace eedb::db;

class inventoryTest : public ::testing::Test
{
public:
    schema::users u;
    schema::user_inventories ui;
    schema::inventories i;
    schema::shelfs sh;

    inventoryTest() {
        db.start_transaction();

        m_userId = test::addUser(db, "xxxxxxx");
        m_invId = test::addInventory(db, "new_inventory_testing", test::login(db, "xxxxxxx") );
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
    auto stat = AclHelper::getAcl(db, m_invId);

    ASSERT_TRUE( stat );
    EXPECT_EQ( m_userId, stat.get().owner() );
}

TEST_F(inventoryTest, userCanEditNewlyCreatedInventory ){
    auth::AccesControl acces(m_userId);
    auth::AccesControl other( test::addUser(db,"xxxxxxx2") );

    EXPECT_TRUE(acces.checkUserAction<schema::inventories>(db, "read", m_invId ) );
    EXPECT_TRUE(acces.checkUserAction<schema::inventories>(db, "write", m_invId ) );
    EXPECT_TRUE(acces.checkUserAction<schema::inventories>(db, "delete", m_invId ) );

    EXPECT_TRUE (other.checkUserAction<schema::inventories>(db, "read", m_invId ) );
    EXPECT_FALSE(other.checkUserAction<schema::inventories>(db, "write", m_invId ) );
    EXPECT_FALSE(other.checkUserAction<schema::inventories>(db, "delete", m_invId ) );
}

