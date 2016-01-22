#include "InventoryHelper.hpp"

#include "sql_schema/stat.h"
#include "sql_schema/shelfs.h"
#include "sql_schema/user_inventories.h"

#include "utils/unixPerms.hpp"

#include "UserHelper.hpp"

using boost::optional;

namespace eedb{
namespace db {
static constexpr schema::inventories i;
static constexpr schema::shelfs s;
static constexpr schema::user_inventories u_i;

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
    auto selectStatement = sqlpp::select(s.uid).from(s).where(s.name == sqlpp::parameter(s.name) and s.inventory_id == parameter(s.inventory_id) );

    auto prepared = db.prepare(selectStatement);
    prepared.params.name = name;
    prepared.params.inventory_id = parentId;

    auto val = db(prepared);

    optional<int64_t> id;
    if(!val.empty())
        id = val.front().uid;
    return id;
}

void InventoryHelper::insertInventory(DB &db, protobuf::MsgInventoryRequest_Add &add)
{
    if(!add.has_acl()){
        auto stat = add.mutable_acl();
        stat->set_owner( eedb::db::UserHelper::getRootId( db ) );
        stat->set_group(2); ///TODO set proper group (some default group)
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

void InventoryHelper::linkWithUser(DB &db, std::shared_ptr<UserData> user, uint64_t inv_id)
{
    db(sqlpp::postgresql::insert_into(u_i).set(
       u_i.inventory_id = inv_id,
           u_i.user_id = user->uid() ) );
}

void InventoryHelper::insertShelf(DB &db, protobuf::MsgInventoryRequest_AddShelf &add)
{
    auto insert =  sqlpp::postgresql::insert_into(s).set(
                s.owner = add.acl().owner(),
                s.stat_group = add.acl().group(),
                s.unixperms = add.acl().unixperms(),
                s.status = add.acl().status(),

                s.name = parameter( s.name ),
                s.description = parameter( s.description ),
                s.inventory_id = add.inventory_id() ).returning(s.uid);

    auto prep = db.prepare(insert);
    prep.params.name = add.name();

    if( add.has_description() )
        prep.params.description = add.description();

    auto inserted = db(prep);
    add.mutable_acl()->set_uid( inserted.front().uid );
}
}
}
