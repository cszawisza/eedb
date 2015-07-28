#pragma once

#include "user.pb.h"
#include "idatabase.h"

#include "sql_schema/t_inventories.h"
#include "sql_schema/t_inventories_history.h"
#include "sql_schema/t_inventories_shelfs.h"
#include "sql_schema/t_inventories_operations.h"

#include "inventory.pb.h"

#include "auth/implementedaction.hpp"
#include "auth/privilege.hpp"
#include "auth/acl.hpp"

using namespace pb;

namespace eedb{
namespace db{

class InventoryHelper {
public:

    static quint64 insertInventory(DB &db, const MsgInventoryRequest_Add &add);
};

}
}
