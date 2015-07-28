//#include "gtest/gtest.h"

//#include <sqlpp11/sqlpp11.h>
//#include <core/database/idatabase.h>
//#include <memory>

//#include "TestCommon.hpp"

//#include "sql_schema/t_shelfs.h"

//#include "core/inventory.hpp"
//#include "core/user.h"

//using eedb::db::UserHelper;
//using namespace test;

//class inventoryTest : public ::testing::Test
//{
//public:
//    schema::t_users u;
//    schema::t_user_inventories ui;
//    schema::t_inventories i;
//    schema::t_shelfs sh;

//    inventoryTest() {
//        db.start_transaction();

//        addUser(db, "xxxxxxx");
//        login("xxxxxxx");
//        inventoryHandler.setUserData(userHandler.user());

//        addInventory("new_inventory_testing");
//    }

//    ~inventoryTest(){
//        db.rollback_transaction(false);
//    }

//    void addInventory( string name )
//    {
//        auto add_inv = pb::MsgInventoryRequest_Add::default_instance();
//        add_inv.set_name( name );
//        add_inv.set_description("description");
//        pb::InventoryShelf *shelf = add_inv.add_shelfs();
//        shelf->set_name("New shelf");
//        shelf->set_description( name );

//        add_inventory(add_inv);
//    }

//    const ResponseCode &login(string name){
//        pb::MsgUserRequest_Login msg;
//        msg.mutable_cred()->set_name(name);
//        msg.set_password("xxxx");

//        pb::ClientRequest req;

//        auto userReq = req.mutable_msguserreq();
//        userReq->mutable_login()->CopyFrom(msg);

//        userHandler.process(db, req);

//        return userHandler.getLastResponse().msguserres().code(0);
//    }

//    bool shelfExists(const char * name){
//        return db(select(exists(select(sh.c_uid).from(sh).where(sh.c_name == name )))).front().exists;
//    }

//    bool inventoryExists(const char * name){
//        return db(select(exists(select(i.c_uid).from(i).where(i.c_name == name )))).front().exists;
//    }

//    const pb::MsgInventoryResponse_Error add_inventory( const pb::MsgInventoryRequest_Add &msg){
//        pb::ClientRequest req;

//        auto userReq = req.mutable_msginventoryreq();
//        userReq->mutable_add()->CopyFrom(msg);

//        inventoryHandler.process(req);

//        return inventoryHandler.getLastResponse().msginventoryres().code(0);
//    }

//    DB db;
//    eedb::handlers::User userHandler;
//    eedb::handlers::Inventory inventoryHandler;
//};

