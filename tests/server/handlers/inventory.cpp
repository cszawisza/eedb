#include "gtest/gtest.h"

#include <sqlpp11/sqlpp11.h>
#include <core/database/idatabase.h>
#include <memory>

#include "../../common.h"

#include "sql_schema/t_user_inventories.h"

#include "core/user.h"
#include "core/storage.h"

class inventoryTest : public ::testing::Test
{
public:
    schema::t_users u;
    schema::t_user_inventories i;

    inventoryTest() {
        createBackup(u);
        createBackup(i);

        addUser("xxxxxxx");
        login("xxxxxxx");
        inventoryHandler.setUserData(userHandler.user());
    }

    ~inventoryTest(){
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

TEST_F(inventoryTest, simpleAdd){
    auto add_inv = pb::MsgInventoryRequest_Add::default_instance();
    add_inv.set_name("neinventory");
    add_inv.set_description("description");

    EXPECT_EQ(pb::MsgInventoryResponse_Error_No_Error,
              add_inventory(add_inv) );
}
