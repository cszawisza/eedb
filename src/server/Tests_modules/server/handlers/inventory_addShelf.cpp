#include "gtest/gtest.h"
#include "TestCommon.hpp"

using namespace eedb::db;
using namespace test;

class inventoryAddShelfTest : public ::testing::Test
{
public:
    schema::users u;
    schema::user_inventories ui;
    schema::inventories i;
    schema::shelfs sh;

    inventoryAddShelfTest() {
        db.start_transaction();

        m_userId = addUser(db, "xxxxxxx");

        auto dat = login(db, "xxxxxxx");

        m_invId = addInventory(db, "new_inventory_testing", dat);
        m_shelfId = addShelf(db, m_invId, "New shelf", dat);
    }

    ~inventoryAddShelfTest(){
        db.rollback_transaction(false);
    }

    DB db;

    uint64_t m_userId= 0;
    uint64_t m_invId= 0;
    uint64_t m_shelfId = 0;
};

TEST_F(inventoryAddShelfTest, checkShelf){
    EXPECT_TRUE( InventoryHelper::getShelfId(db, m_invId, "New shelf").is_initialized() );
}

TEST_F(inventoryAddShelfTest, checkAcl){
    auto stat = AclHelper::getAcl(db, InventoryHelper::getShelfId(db, m_invId, "New shelf").get_value_or(0) );

    ASSERT_TRUE( stat );
    EXPECT_EQ( m_userId, stat.get().owner() );
}

TEST_F(inventoryAddShelfTest, userCanEditNewlyCreatedShelf ){
    auth::AccesControl acces(m_userId);

    EXPECT_TRUE(acces.checkUserAction<schema::shelfs>(db, "read", m_shelfId ) );
    EXPECT_TRUE(acces.checkUserAction<schema::shelfs>(db, "write", m_shelfId ) );
    EXPECT_TRUE(acces.checkUserAction<schema::shelfs>(db, "delete", m_shelfId ) );
}

