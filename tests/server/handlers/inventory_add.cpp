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
    schema::t_users u;
    schema::t_user_inventories ui;
    schema::t_inventories i;
    schema::t_shelfs sh;

    inventoryTest() {
        db.start_transaction();

        m_userId = addUser(db, "xxxxxxx");
        inventoryHandler.setUserData( login(db, "xxxxxxx") );

        addInventory("new_inventory_testing");
    }

    ~inventoryTest(){
        db.rollback_transaction(false);
    }

    void addInventory( string name )
    {
        auto add_inv = pb::MsgInventoryRequest_Add::default_instance();
        add_inv.set_name( name );
        add_inv.set_description("description");
        pb::InventoryShelf *shelf = add_inv.add_shelfs();
        shelf->set_name("New shelf 1");
        shelf->set_description( name );
        shelf = add_inv.add_shelfs();
        shelf->set_name("New shelf 2");
        shelf->set_description( name );

        add_inventory(add_inv);
        m_invId = InventoryHelper::getIdByName(db, "new_inventory_testing");
    }

    bool shelfExists(const char * name){
        return db(select(exists(select(sh.c_uid).from(sh).where(sh.c_name == name )))).front().exists;
    }

    bool inventoryExists(const char * name){
        return db(select(exists(select(i.c_uid).from(i).where(i.c_name == name )))).front().exists;
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

    quint64 m_userId= 0;
    quint64 m_invId= 0;
};

TEST_F(inventoryTest, checkInventory){
    EXPECT_TRUE( inventoryExists("new_inventory_testing") );
}

TEST_F(inventoryTest, checkShelf){
    EXPECT_TRUE( shelfExists("New shelf 1") );
    EXPECT_TRUE( shelfExists("New shelf 2") );
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

