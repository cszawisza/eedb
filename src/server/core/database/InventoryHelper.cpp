#include "InventoryHelper.hpp"

#include "sql_schema/t_acl.h"
#include "utils/unixPerms.hpp"

namespace eedb{
namespace db {

quint64 InventoryHelper::insertInventory(DB &db, const MsgInventoryRequest_Add &add)
{
    static constexpr schema::t_inventories i;

    auto insert = insert_into(i).set(
                i.c_owner = add.acl().owner(),
                i.c_name = parameter(i.c_name),
                i.c_group = (int)auth::GROUP_inventories,
                i.c_unixperms = UnixPermissions("rwdr-----").toInteger()
            );
    auto query = db.prepare(insert);

    query.params.c_name = add.name();
    db(query);

    ///TODO change to .RETURNING when implemented
    return db.lastInsertId( sqlpp::tableName<schema::t_acl>(), "c_uid" );
}

}
}
