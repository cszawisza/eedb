#include "gtest/gtest.h"

#include <sqlpp11/sqlpp11.h>
#include "sql_schema/shelfs.h"

#include <core/database/idatabase.h>
#include <core/inventory.hpp>

#include "TestCommon.hpp"



using namespace test;

class inventoryGetTest : public ::testing::Test
{
public:
    schema::users u;
    schema::user_inventories ui;
    schema::inventories i;
    schema::shelfs sh;

    inventoryGetTest() {
        db.start_transaction();

        m_userId = addUser(db, "xxxxxxx");
        inventoryHandler.setUserData( login(db, "xxxxxxx") );

        addInventory("new_inventory_testing_1");
//        addInventory("new_inventory_testing_2");
//        addInventory("new_inventory_testing_3");
    }

    ~inventoryGetTest(){
        db.rollback_transaction(false);
    }

    void addInventory( string name )
    {
        auto add_inv = pb::MsgInventoryRequest_Add::default_instance();
        add_inv.set_name( name );
        add_inv.set_description("description");
        add_inventory(add_inv);
    }

    const pb::MsgInventoryResponse_Error add_inventory( const pb::MsgInventoryRequest_Add &msg){
        pb::ClientRequest req;

        auto userReq = req.mutable_msginventoryreq();
        userReq->mutable_add()->CopyFrom(msg);

        inventoryHandler.process(db, req);

        return inventoryHandler.getLastResponse().msginventoryres().code(0);
    }

    DB db;
    eedb::handlers::User userHandler;
    eedb::handlers::Inventory inventoryHandler;

    uint64_t m_userId = 0;
    uint64_t m_invId = 0;
};

TEST_F(inventoryGetTest, getInventory ){
    pb::ClientRequest req;
    auto get = req.mutable_msginventoryreq()->mutable_get();
    get->CopyFrom( MsgInventoryRequest_Get::default_instance() );

    get->mutable_where()->set_user_id( m_userId );
    inventoryHandler.process(db, req);

    auto res = inventoryHandler.getLastResponse().msginventoryres();

    EXPECT_NE( res.id(), 0 );
    EXPECT_STREQ( res.name().c_str(), "new_inventory_testing_1");
    EXPECT_STREQ( res.description().c_str(), "description");
}
