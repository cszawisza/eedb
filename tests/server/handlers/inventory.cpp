#include "gtest/gtest.h"

#include <sqlpp11/sqlpp11.h>
#include <core/database/idatabase.h>
#include <memory>

#include "../../common.h"

#include "sql_schema/t_shelfs.h"
#include "sql_schema/t_user_inventories.h"
#include "sql_schema/t_inventories.h"
#include "sql_schema/t_users.h"
#include "sql_schema/t_inventories_shelfs.h"

#include "core/user.h"
#include "core/inventory.hpp"

class inventoryTest : public ::testing::Test
{
public:
    schema::t_users u;
    schema::t_user_inventories ui;
    schema::t_inventories i;
    schema::t_shelfs sh;

    inventoryTest() {
        createBackup(u);
        createBackup(i);
        createBackup(sh);

        addUser("xxxxxxx");
        login("xxxxxxx");
        inventoryHandler.setUserData(userHandler.user());

        auto add_inv = pb::MsgInventoryRequest_Add::default_instance();
        add_inv.set_name("new_inventory_testing");
        add_inv.set_description("description");
        pb::InventoryShelf *shelf = add_inv.add_shelfs();
        shelf->set_name("New shelf");
        shelf->set_description("New shelf description");

         add_inventory(add_inv);
    }

    ~inventoryTest(){
        restoreBackup(sh);
        restoreBackup(i);
        restoreBackup(u);
    }

    const ResponseCode &addUser(string name){
        pb::MsgUserRequest_Add msg;
        msg.mutable_basic()->set_name(name);
        msg.mutable_basic()->set_email(name + "@fake.xx");
        msg.set_password("xxxx");

        pb::ClientRequest req;

        auto userReq = req.mutable_msguserreq();
        userReq->mutable_add()->CopyFrom(msg);

        userHandler.process(req);

        return userHandler.getLastResponse().msguserres().code(0);
    }

    const ResponseCode &login(string name){
        pb::MsgUserRequest_Login msg;
        msg.mutable_cred()->set_name(name);
        msg.set_password("xxxx");

        pb::ClientRequest req;

        auto userReq = req.mutable_msguserreq();
        userReq->mutable_login()->CopyFrom(msg);

        userHandler.process(req);

        return userHandler.getLastResponse().msguserres().code(0);
    }

    bool shelfExists(const char * name){
        DB db;
        return db(select(exists(select(sh.c_uid).from(sh).where(sh.c_name == name )))).front().exists;
    }

    bool inventoryExists(const char * name){
        DB db;
        return db(select(exists(select(i.c_uid).from(i).where(i.c_name == name )))).front().exists;
    }

    const pb::MsgInventoryResponse_Error add_inventory( const pb::MsgInventoryRequest_Add &msg){
        pb::ClientRequest req;

        auto userReq = req.mutable_msginventoryreq();
        userReq->mutable_add()->CopyFrom(msg);

        inventoryHandler.process(req);

        return inventoryHandler.getLastResponse().msginventoryres().code(0);
    }

    eedb::handlers::User userHandler;
    eedb::handlers::Inventory inventoryHandler;
};

TEST_F(inventoryTest, checkInventory){
    EXPECT_TRUE( inventoryExists("new_inventory_testing") );
}

TEST_F(inventoryTest, checkShelf){
    EXPECT_TRUE( shelfExists("New shelf") );
}
