#include "TestCommon.hpp"


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



quint64 test::addShelf(DB &db, uint64_t storageId, string name, SharedUserData data){
    protobuf::ClientRequest req;

    auto add = protobuf::MsgInventoryRequest_AddShelf::default_instance();
    add.set_name( name );
    add.set_description("description");
    add.set_inventory_id( storageId );

    auto userReq = req.mutable_msginventoryreq();
    userReq->mutable_addshelf()->CopyFrom(add);
    eedb::pu::InventoryPU inventoryHandler;
    inventoryHandler.setUserData(data);
    inventoryHandler.process(db, req);

    //    return inventoryHandler.getLastResponse().msginventoryres().code(0);
    return eedb::db::InventoryHelper::getShelfId(db, storageId, name).get_value_or(0);
}


SharedUserData test::login(DB &db, const string &name, const string &pass){
    protobuf::UserReq_Login msg;
    msg.mutable_cred()->set_nickname(name);
    msg.set_password(pass);

    protobuf::ClientRequest req;

    auto userReq = req.mutable_userreq();
    userReq->mutable_login()->CopyFrom(msg);
    eedb::pu::UserPU userHandler;
    userHandler.process(db, req);
    return userHandler.user();
}


quint64 test::addUser(DB &db, const string &name, const string &pass){
    constexpr schema::users u;
    auto msg = std::make_shared<requests::user::Add>();

    msg->set_nickname(name);
    msg->set_email(name + "@fake.xx");
    msg->set_password(pass);

    if(! db( UserHelper::selectExists( u.name == name )).front().exists ) // function returns 0 when user don't exist
        UserHelper::insertUser(db, *msg);

    return db(UserHelper::selectId( u.name == name )).front().uid;
}


quint64 test::addInventory(DB &db, string name, SharedUserData data)
{
    protobuf::ClientRequest req;
    eedb::pu::InventoryPU inventoryHandler;
    inventoryHandler.setUserData( data );

    auto add_inv = protobuf::MsgInventoryRequest_Add::default_instance();
    add_inv.set_name( name );
    add_inv.set_description("description");

    auto userReq = req.mutable_msginventoryreq();
    userReq->mutable_add()->CopyFrom(add_inv);
    inventoryHandler.process(db, req);

    //    auto returnCode = inventoryHandler.getLastResponse().msginventoryres().code(0);
    return eedb::db::InventoryHelper::getInventoryIdByName(db, name ).get_value_or(0);
}
