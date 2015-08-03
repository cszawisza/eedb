#include "InventoryHelper.hpp"

#include "sql_schema/t_acl.h"
#include "sql_schema/t_shelfs.h"
#include "sql_schema/t_user_inventories.h"

#include "utils/unixPerms.hpp"

namespace eedb{
namespace db {
static constexpr schema::t_inventories i;
static constexpr schema::t_inventories_shelfs i_s;
static constexpr schema::t_shelfs s;
static constexpr schema::t_user_inventories u_i;

quint64 InventoryHelper::getIdByName(DB &db, const string &name)
{
    ///TODO prevent sql injection
    auto val = db(sqlpp::select(i.c_uid).from(i).where(i.c_name == name) );
    if(!val.empty())
        return val.front().c_uid;
    else
        return 0;
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

    auto insert = insert_into(i).set(
                i.c_owner = add.acl().owner(),
                i.c_group = (int)auth::GROUP_inventories,
                i.c_unixperms = add.acl().has_unixperms() ? add.acl().unixperms()
                                                          : UnixPermissions("rwdr-----").toInteger(),
                i.c_status = add.acl().has_status() ? add.acl().status()
                                                    : auth::State_Normal,
                i.c_name = parameter(i.c_name)
            );
    auto query = db.prepare(insert);

    query.params.c_name = add.name();

    db(query);

    ///TODO change to .RETURNING when implemented
    add.mutable_acl()->set_uid(db.lastInsertId( sqlpp::tableName<schema::t_acl>(), "c_uid" ));
}

void InventoryHelper::linkWithUser(DB &db, SharedUserData user, quint64 inv_id)
{
    db(insert_into(u_i).set(
       u_i.c_inventory_id = inv_id,
           u_i.c_user_id = user->id() ) );
}

void InventoryHelper::addShelfs(DB &db, const ::google::protobuf::RepeatedPtrField<InventoryShelf> &add)
{
    ///TODO use prepared statements
    auto insert_statement = insert_into(s).columns(
                s.c_owner,
                s.c_group,
                s.c_unixperms,
                s.c_name,
                s.c_description
                );

    for( const InventoryShelf &shelf : add ){
        insert_statement.values.add(
                    s.c_owner = shelf.acl().owner(),
                    s.c_group = shelf.acl().group(),
                    s.c_unixperms = shelf.acl().unixperms(),

                    s.c_name = shelf.name(),
                    s.c_description = shelf.description() );
        db(insert_statement);
        ///TODO change to returning
        auto shelfId = db.lastInsertId(sqlpp::tableName<schema::t_acl>(),"c_uid" );

        db(insert_into(i_s).set(i_s.c_inventory_id = shelf.inventory_id(), i_s.c_shelf = shelfId )  );
    }
}




}
}
