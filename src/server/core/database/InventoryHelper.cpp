#include "InventoryHelper.hpp"

#include "sql_schema/stat.h"
#include "sql_schema/t_shelfs.h"
#include "sql_schema/t_user_inventories.h"

#include "utils/unixPerms.hpp"

using boost::optional;

namespace eedb{
namespace db {
static constexpr schema::t_inventories i;
static constexpr schema::t_shelfs s;
static constexpr schema::t_user_inventories u_i;

using sqlpp::postgresql::insert_into;

optional<int64_t> InventoryHelper::getInventoryIdByName(DB &db, const string &name)
{
    auto val = db.prepare(sqlpp::select(i.uid).from(i).where(i.name == parameter(i.name) ) );
    val.params.name = name;
    auto row = db(val);

    optional<int64_t> id;
    if(!row.empty())
        id = row.front().uid;
    return id;
}

optional<int64_t> InventoryHelper::getShelfId(DB &db, uint64_t parentId, const string &name)
{
    ///TODO prevent sql injection
    auto val = db(sqlpp::select(s.uid).from(s).where(s.name == name and s.c_inventory_id == parentId ));

    optional<int64_t> id;
    if(!val.empty())
        id = val.front().uid;
    return id;
}

void InventoryHelper::insertInventory(DB &db, MsgInventoryRequest_Add &add)
{
    if(!add.has_acl()){
        auto stat = add.mutable_acl();
        stat->set_owner(1); ///TODO set proper root id
        stat->set_group(2); ///TOFO set proper group (some default group)
        stat->set_status( auth::State_Normal );
        stat->set_unixperms( UnixPermissions("-rwdrw-r--").toInteger() );
    }

    auto insert = sqlpp::postgresql::insert_into(i).set(
                i.owner = add.acl().owner(),
                i.stat_group = (int)auth::GROUP_inventories,
                i.unixperms = add.acl().has_unixperms() ? add.acl().unixperms()
                                                          : UnixPermissions("rwdr-----").toInteger(),
                i.status = add.acl().has_status() ? add.acl().status()
                                                    : auth::State_Normal,
                i.description = parameter(i.description),
                i.name = parameter(i.name)
            ).returning(i.uid);
    auto query = db.prepare(insert);

    query.params.name = add.name();
    if(add.has_description())
        query.params.description = add.description();

    auto inserted = db(query);

    add.mutable_acl()->set_uid(inserted.front().uid);
}

void InventoryHelper::linkWithUser(DB &db, SharedUserData user, uint64_t inv_id)
{
    db(sqlpp::postgresql::insert_into(u_i).set(
       u_i.c_inventory_id = inv_id,
           u_i.c_user_id = user->id() ) );
}

void InventoryHelper::insertShelf(DB &db, MsgInventoryRequest_AddShelf &add)
{
    auto insert =  sqlpp::postgresql::insert_into(s).set(
                s.owner = add.acl().owner(),
                s.stat_group = add.acl().group(),
                s.unixperms = add.acl().unixperms(),
                s.status = add.acl().status(),

                s.name = parameter( s.name ),
                s.description = parameter( s.description ),
                s.c_inventory_id = add.inventory_id() ).returning(s.uid);

    auto prep = db.prepare(insert);
    prep.params.name = add.name();

    if( add.has_description() )
        prep.params.description = add.description();

    auto inserted = db(prep);
    add.mutable_acl()->set_uid( inserted.front().uid );
}
}
}
