#pragma once

#include "clientcache.h"

#include "user.pb.h"
#include "idatabase.h"

#include "sqlpp11/sqlpp11.h"
#include "sql_schema/t_inventories.h"
#include "sql_schema/t_inventories_history.h"
#include "sql_schema/t_inventories_operations.h"
#include "sql_schema/t_user_inventories.h"
#include "sql_schema/t_shelfs.h"

#include "inventory.pb.h"

#include "auth/implementedaction.hpp"
#include "auth/privilege.hpp"
#include "auth/acl.hpp"

#include <boost/optional.hpp>

using namespace pb;
using boost::optional;

namespace eedb{
namespace db{

class InventoryHelper {
public:

    static optional<int64_t> getInventoryIdByName( DB &db, const std::string &name);
    static optional<int64_t> getShelfId(DB &db, uint64_t parentId, const std::string &name );
    static void insertInventory(DB &db, MsgInventoryRequest_Add &add);
    static void linkWithUser(DB &db, SharedUserData user, uint64_t inv_id );
    static void insertShelf(DB &db, MsgInventoryRequest_AddShelf &add );
};

}
}
