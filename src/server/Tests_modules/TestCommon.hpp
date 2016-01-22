#pragma once

#include <string>
#include <memory>

class UserData;
class DB;

namespace test{

extern uint64_t addUser(DB &db, const std::string &name, const std::string &pass = "xxxx");

extern std::shared_ptr<UserData> login(DB &db, const std::string &name, const std::string &pass = "xxxx");

//extern quint64 addInventory(DB &db, string name, SharedUserData data );

//extern quint64 addShelf(DB &db,uint64_t storageId, string name, SharedUserData data );

extern std::string random_string( size_t length );

}
