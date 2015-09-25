#pragma once

#include <string>
#include <memory>

#include <sqlpp11/sqlpp11.h>
#include <sqlpp11/sqlpp11.h>

#include <core/inventory.hpp>

#include <sql_schema/t_shelfs.h>

#include "database/idatabase.h"
#include "database/AclHelper.hpp"
#include "database/InventoryHelper.hpp"
#include "database/UserHelper.hpp"

#include "user.h"

using std::string;

namespace test{

using eedb::db::UserHelper;

inline quint64 addUser(DB &db, const string &name, const std::string &pass = "xxxx"){
    constexpr schema::t_users u;
    pb::UserReq_Add msg;

    msg.mutable_basic()->set_name(name);
    msg.mutable_basic()->set_email(name + "@fake.xx");
    msg.set_password(pass);

    if(! db( UserHelper::selectExists( u.c_name == name )).front().exists ) // function returns 0 when user don't exist
        UserHelper::insertUser(db, msg);

    return db(UserHelper::selectId( u.c_name == name )).front().c_uid;
}

inline SharedUserData login(DB &db, const string &name, const std::string &pass = "xxxx"){
    pb::UserReq_Login msg;
    msg.mutable_cred()->set_name(name);
    msg.set_password(pass);

    pb::ClientRequest req;

    auto userReq = req.mutable_userreq();
    userReq->mutable_login()->CopyFrom(msg);
    eedb::handlers::User userHandler;
    userHandler.process(db, req);
    return userHandler.user();
}

inline quint64 addInventory(DB &db, string name, SharedUserData data )
{
    pb::ClientRequest req;
    eedb::handlers::Inventory inventoryHandler;
    inventoryHandler.setUserData( data );

    auto add_inv = pb::MsgInventoryRequest_Add::default_instance();
    add_inv.set_name( name );
    add_inv.set_description("description");

    auto userReq = req.mutable_msginventoryreq();
    userReq->mutable_add()->CopyFrom(add_inv);
    inventoryHandler.process(db, req);

//    auto returnCode = inventoryHandler.getLastResponse().msginventoryres().code(0);
    return eedb::db::InventoryHelper::getInventoryIdByName(db, name ).get_value_or(0);
}

inline quint64 addShelf(DB &db,uint64_t storageId, string name, SharedUserData data ){
    pb::ClientRequest req;

    auto add = pb::MsgInventoryRequest_AddShelf::default_instance();
    add.set_name( name );
    add.set_description("description");
    add.set_inventory_id( storageId );

    auto userReq = req.mutable_msginventoryreq();
    userReq->mutable_addshelf()->CopyFrom(add);
    eedb::handlers::Inventory inventoryHandler;
    inventoryHandler.setUserData(data);
    inventoryHandler.process(db, req);

//    return inventoryHandler.getLastResponse().msginventoryres().code(0);
    return eedb::db::InventoryHelper::getShelfId(db, storageId, name).get_value_or(0);
}

inline std::string random_string( size_t length )
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

}
