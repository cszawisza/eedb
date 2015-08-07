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

class inventoryAddShelfTest : public ::testing::Test
{
public:
    schema::t_users u;
    schema::t_user_inventories ui;
    schema::t_inventories i;
    schema::t_shelfs sh;

    inventoryAddShelfTest() {
        db.start_transaction();

        m_userId = addUser(db, "xxxxxxx");
        inventoryHandler.setUserData( login(db, "xxxxxxx") );

        addInventory("new_inventory_testing");
        addShelf("New shelf");
    }

    ~inventoryAddShelfTest(){
        db.rollback_transaction(false);
    }

    void addInventory( string name )
    {
        auto add_inv = pb::MsgInventoryRequest_Add::default_instance();
        add_inv.set_name( name );
        add_inv.set_description("description");
        add_inventory(add_inv);
        m_invId = InventoryHelper::getInventoryIdByName(db, name);
    }

    void addShelf( string name )
    {
        auto add = pb::MsgInventoryRequest_AddShelf::default_instance();
        add.set_name( name );
        add.set_description("description");
        add.set_inventory_id( m_invId );
        add_shelf(add);
    }

    const pb::MsgInventoryResponse_Error add_inventory( const pb::MsgInventoryRequest_Add &msg){
        pb::ClientRequest req;

        auto userReq = req.mutable_msginventoryreq();
        userReq->mutable_add()->CopyFrom(msg);

        inventoryHandler.process(db, req);

        return inventoryHandler.getLastResponse().msginventoryres().code(0);
    }

    const pb::MsgInventoryResponse_Error add_shelf( const pb::MsgInventoryRequest_AddShelf &msg){
        pb::ClientRequest req;

        auto userReq = req.mutable_msginventoryreq();
        userReq->mutable_addshelf()->CopyFrom(msg);

        inventoryHandler.process(db, req);

        return inventoryHandler.getLastResponse().msginventoryres().code(0);
    }

    DB db;
    eedb::handlers::User userHandler;
    eedb::handlers::Inventory inventoryHandler;

    uint64_t m_userId= 0;
    uint64_t m_invId= 0;
};

TEST_F(inventoryAddShelfTest, checkShelf){
    EXPECT_TRUE( InventoryHelper::getShelfId(db, m_invId, "New shelf") > 0 );
}

TEST_F(inventoryAddShelfTest, checkAcl){
    auto acl = AclHelper::getAcl(db, InventoryHelper::getShelfId(db, m_invId, "New shelf"));
    EXPECT_EQ( m_userId, acl.owner() );
}

TEST_F(inventoryAddShelfTest, userCanEditNewlyCreatedShelf ){
    auth::AccesControl acces(m_userId);
    auto shelfId = InventoryHelper::getShelfId(db, m_invId, "New shelf");

    EXPECT_TRUE(acces.checkUserAction<schema::t_shelfs>(db, "read", shelfId ) );
    EXPECT_TRUE(acces.checkUserAction<schema::t_shelfs>(db, "write", shelfId ) );
    EXPECT_TRUE(acces.checkUserAction<schema::t_shelfs>(db, "delete", shelfId ) );
}

