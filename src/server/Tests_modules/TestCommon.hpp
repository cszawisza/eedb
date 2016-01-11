#pragma once

#include <string>
#include <memory>

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

#include "database/idatabase.h"
#include "database/AclHelper.hpp"
#include "database/InventoryHelper.hpp"
#include "database/UserHelper.hpp"
#include "database/CategoryHelper.hpp"


#include "DataStructures/Adapters/Protobuf/UserRequestAdapter.hpp"

using std::string;

namespace test{

using eedb::db::UserHelper;

extern quint64 addUser(DB &db, const string &name, const std::string &pass = "xxxx");

extern SharedUserData login(DB &db, const string &name, const std::string &pass = "xxxx");

//extern quint64 addInventory(DB &db, string name, SharedUserData data );

//extern quint64 addShelf(DB &db,uint64_t storageId, string name, SharedUserData data );

extern std::string random_string( size_t length );

}
