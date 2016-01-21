#include "TestCommon.hpp"

#include "DataStructures/Adapters/Protobuf/ClientRequestAdapter.hpp"
#include "DataStructures/Adapters/Protobuf/ServerResponseAdapter.hpp"

#include "DataStructures/Adapters/Protobuf/CategoryRequestAdapter.hpp"
#include "DataStructures/Adapters/Protobuf/UserRequestAdapter.hpp"

#include "DataStructures/Adapters/Protobuf/UserResponseAdapter.hpp"
#include "DataStructures/Adapters/Protobuf/CategoryResponseAdapter.hpp"

#include "message_conteiner.pb.h"
#include "common.pb.h"
#include "user.pb.h"

#include "database/idatabase.h"
#include "database/AclHelper.hpp"
#include "database/InventoryHelper.hpp"
#include "database/UserHelper.hpp"
#include "database/CategoryHelper.hpp"

#include <sqlpp11/sqlpp11.h>

#include "ProcessingUnits/InventoryPU.hpp"
#include "ProcessingUnits/UserPU.hpp"
#include "ProcessingUnits/CategoryPU.hpp"
#include "ProcessingUnits/ItemPU.hpp"

#include "sql_schema/items.h"
#include "sql_schema/item_files.h"
#include "sql_schema/users.h"
#include "sql_schema/user_history.h"
#include "sql_schema/shelfs.h"
#include "sql_schema/inventories.h"
#include "sql_schema/files.h"
#include "sql_schema/categories.h"
#include "sql_schema/category_files.h"

using namespace eedb::db;

string test::random_string(size_t length)
{
    auto randchar = []() -> char
    {
            const char charset[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
            const size_t max_index = (sizeof(charset) - 1);
            return charset[ rand() % max_index ];
};
std::string str(length,0);
std::generate_n( str.begin(), length, randchar );
return str;
}

//quint64 test::addShelf(DB &db, uint64_t storageId, string name, SharedUserData data){
//    protobuf::ClientRequest req;

//    auto add = protobuf::MsgInventoryRequest_AddShelf::default_instance();
//    add.set_name( name );
//    add.set_description("description");
//    add.set_inventory_id( storageId );

//    auto userReq = req.mutable_msginventoryreq();
//    userReq->mutable_addshelf()->CopyFrom(add);
//    eedb::pu::InventoryPU inventoryHandler;
//    inventoryHandler.setUserData(data);
//    inventoryHandler.process(db, req);

//    //    return inventoryHandler.getLastResponse().msginventoryres().code(0);
//    return eedb::db::InventoryHelper::getShelfId(db, storageId, name).get_value_or(0);
//}

std::shared_ptr<UserData> test::login(DB &db, const string &name, const string &pass){

    // set pb namespace
    auto req = ClientRequest();
    auto loginReq = req.user()->login();
    loginReq->set_password(pass);
    loginReq->credentials()->set_authorization(name);

    eedb::pu::UserPU userHandler;
    userHandler.setOutputData( std::make_shared<ServerResponse>() );
    userHandler.process(db, &req);
    return userHandler.user();
}

uint64_t test::addUser(DB &db, const string &name, const string &pass){
    constexpr schema::users u;
    auto msg = std::make_shared<requests::user::Add>();

    msg->set_nickname(name);
    msg->set_email(name + "@fake.xx");
    msg->set_password(pass);

    if(! db( UserHelper::selectExists( u.name == name )).front().exists ) // function returns 0 when user don't exist
        UserHelper::insertUser(db, *msg);

    return db(UserHelper::selectId( u.name == name )).front().uid;
}

//quint64 test::addInventory(DB &db, string name, SharedUserData data)
//{
//    protobuf::ClientRequest req;
//    eedb::pu::InventoryPU inventoryHandler;
//    inventoryHandler.setUserData( data );

//    auto add_inv = protobuf::MsgInventoryRequest_Add::default_instance();
//    add_inv.set_name( name );
//    add_inv.set_description("description");

//    auto userReq = req.mutable_msginventoryreq();
//    userReq->mutable_add()->CopyFrom(add_inv);
//    inventoryHandler.process(db, req);

//    //    auto returnCode = inventoryHandler.getLastResponse().msginventoryres().code(0);
//    return eedb::db::InventoryHelper::getInventoryIdByName(db, name ).get_value_or(0);
//}
