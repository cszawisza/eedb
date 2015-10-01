#include "InventoryHelper.hpp"

#include "sql_schema/t_acl.h"
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
    auto val = db.prepare(sqlpp::select(i.c_uid).from(i).where(i.c_name == parameter(i.c_name) ) );
    val.params.c_name = name;
    auto row = db(val);

    optional<int64_t> id;
    if(!row.empty())
        id = row.front().c_uid;
    return id;
}

optional<int64_t> InventoryHelper::getShelfId(DB &db, uint64_t parentId, const string &name)
{
    ///TODO prevent sql injection
    auto val = db(sqlpp::select(s.c_uid).from(s).where(s.c_name == name and s.c_inventory_id == parentId ));

    optional<int64_t> id;
    if(!val.empty())
        id = val.front().c_uid;
    return id;
}

void InventoryHelper::insertInventory(DB &db, MsgInventoryRequest_Add &add)
{
    if(!add.has_acl()){
        auto acl = add.mutable_acl();
        acl->set_owner(1); ///TODO set proper root id
        acl->set_group(2); ///TOFO set proper group (some default group)
        acl->set_status( auth::State_Normal );
        acl->set_unixperms( UnixPermissions("-rwdrw-r--").toInteger() );
    }

    auto insert = sqlpp::postgresql::insert_into(i).set(
                i.c_owner = add.acl().owner(),
                i.c_group = (int)auth::GROUP_inventories,
                i.c_unixperms = add.acl().has_unixperms() ? add.acl().unixperms()
                                                          : UnixPermissions("rwdr-----").toInteger(),
                i.c_status = add.acl().has_status() ? add.acl().status()
                                                    : auth::State_Normal,
                i.c_description = parameter(i.c_description),
                i.c_name = parameter(i.c_name)
            ).returning(i.c_uid);
    auto query = db.prepare(insert);

    query.params.c_name = add.name();
    if(add.has_description())
        query.params.c_description = add.description();

    auto inserted = db(query);

    add.mutable_acl()->set_uid(inserted.front().c_uid);
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
                s.c_owner = add.acl().owner(),
                s.c_group = add.acl().group(),
                s.c_unixperms = add.acl().unixperms(),
                s.c_status = add.acl().status(),

                s.c_name = parameter( s.c_name ),
                s.c_description = parameter( s.c_description ),
                s.c_inventory_id = add.inventory_id() ).returning(s.c_uid);

    auto prep = db.prepare(insert);
    prep.params.c_name = add.name();

    if( add.has_description() )
        prep.params.c_description = add.description();

    auto inserted = db(prep);
    add.mutable_acl()->set_uid( inserted.front().c_uid );
}
}
}
