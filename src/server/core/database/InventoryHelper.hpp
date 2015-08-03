#pragma once

#include "clientcache.h"

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

    static quint64 getIdByName( DB &db, const std::string &name);
    static void insertInventory(DB &db, MsgInventoryRequest_Add &add);
    static void linkWithUser(DB &db, SharedUserData user, quint64 inv_id );
    static void addShelfs(DB &db, const ::google::protobuf::RepeatedPtrField< ::pb::InventoryShelf > &add );
};

}
}
