#include "storage.h"

#include "sql_schema/t_inventories.h"
#include "sql_schema/t_inventories_history.h"
#include "sql_schema/t_inventories_operations.h"
#include "sql_schema/t_inventories_shelfs.h"
#include "sql_schema/t_user_inventories.h"
#include "sql_schema/t_shelfs.h"

#include "sqlpp11/sqlpp11.h"

#include <iostream>

schema::t_inventories i;
schema::t_user_inventories u_i;
schema::t_inventories_shelfs i_s;

using namespace pb;
using namespace schema;

namespace eedb{
namespace handlers{

void Inventory::process(pb::ClientRequest &msg )
{
    // Check if this is the message that handler wants
    Q_ASSERT( msg.data_case() == pb::ClientRequest::kMsgInventoryReq );
    Q_ASSERT( msg.has_msginventoryreq() );

    if (!user()->isOnline()){
        addResp(true, Error_AccesDeny);
        return;
    }

    auto req = msg.msginventoryreq();

    MsgInventoryRequest::ActionCase msgType = req.action_case();
    switch ( msgType ) {
    case MsgInventoryRequest::kAdd:
        handle_add( *req.mutable_add() );
        break;
    case MsgInventoryRequest::kGet:
        handle_get( *req.mutable_get() );
        break;
    case MsgInventoryRequest::kRemove:
        handle_remove( *req.mutable_remove() );
        break;
    case MsgInventoryRequest::kModify:
        handle_modify( *req.mutable_modify() );
        break;
    case MsgInventoryRequest::kAddShelf:
        handle_addShelf( *req.mutable_addshelf() );
        break;
    case MsgInventoryRequest::ACTION_NOT_SET:
        addResp(true, Error_NoActionChoosen);
        break;
    }
}

void Inventory::handle_add( MsgInventoryRequest_Add &msg)
{
    if(msg.name().length() > 250 ){

    }
    if(msg.description().length() > 100000 ){
//        addResp(true, );
    }

    ///TODO check if acl in msgReq has owner fields (if not, set owner as this user)

    DB db;
    auth::AccesControl acl( user()->id() );
    if(acl.checkUserAction<t_acl>(db, "write")){
        // can modify acl
    }

    if(acl.checkUserAction<t_inventories>(db, "write") ){
        bool error=false;
        try{
            db.start_transaction();
            insertStorage(db, msg);
        }
        catch(sqlpp::exception e){
            error = true;
            db.rollback_transaction(false);
        }
        if(!error)
            db.commit_transaction();
    }
    else
        addResp(true, Error_AccesDeny);

}

quint64 Inventory::doInsert(DB &db, const MsgInventoryRequest_Add &msgReq)
{
    auto insert = insert_into(i).set(
                i.c_name = parameter(i.c_name),
                i.c_owner = user()->id(),
                i.c_group = (int)auth::GROUP_inventories,
                i.c_unixperms = 494 ///TODO check
            );
    auto query = db.prepare(insert);

    query.params.c_name = msgReq.name();
    db(query);

    ///TODO change to .RETURNING when implemented
    return db.lastInsertId("t_inventories", "c_uid");
}

void Inventory::linkInventoryWithUser(DB &db, quint64 inventoryId)
{
        db(insert_into(u_i).set(
           u_i.c_inventory_id = inventoryId,
           u_i.c_user_id = user()->id() ) );
}

void Inventory::insertStorage(DB &db, const MsgInventoryRequest_Add &msgReq ){
    quint64 inventoryId = doInsert(db, msgReq);
    linkInventoryWithUser(db,  inventoryId);

    constexpr schema::t_inventories i;

    auto insert_statement = insert_into(i).columns(
                i.c_name,
                i.c_owner,
                i.c_description
                );

//    for( const auto &shelf : msg.shelfs() ){
//        insert_statement.values.add(
//                    s.c_name = shelf.name(),
//                    s.c_owner = user()->id(),
//                    s.c_description = shelf.description() );
//        db(insert_statement);
//    }

}

void Inventory::handle_get( const MsgInventoryRequest_Get &msg)
{
    ///TODO check if inventory with id exists!
//    if(db(select(exists(select(c_uid)))))

    auto &where = msg.where();

    quint64 uid = user()->id() ;

    DB db;
    auth::AccesControl acl(uid);
    const int oid = msg.id();

    if(where.has_user_id()){
        // get all user inventories

        auto dyn_sel = dynamic_select( db.connection())
                .dynamic_columns(i.c_uid)
                .from(i)
                .dynamic_where( i.c_uid == oid );

        if( msg.has_acl() && msg.acl()){
            dyn_sel.selected_columns.add(i.c_owner);
            dyn_sel.selected_columns.add(i.c_group);
            dyn_sel.selected_columns.add(i.c_unixperms);
            dyn_sel.selected_columns.add(i.c_status);
        }

        if( msg.has_name() && msg.name())
            dyn_sel.selected_columns.add(i.c_name);
        if( msg.has_description() && msg.description())
            dyn_sel.selected_columns.add(i.c_description);

        ///TODO get all storage shelfs
    }
    else if(where.has_inventory_id() ){
        // get inventory with given ID
        if(!acl.checkUserAction<t_inventories>("read", where.inventory_id() )){
            ///TODO acces deny
            return;
        }
    }

//    if(acl.checkUserAction("read", msg.id() )){
//        ///TODO get data
//        auto dyn_sel = dynamic_select( db.connection())
//                .dynamic_columns(i.c_uid)
//                .from(i)
//                .dynamic_where( i.c_uid == oid );
//        if( msg.has_acl() && msg.acl() == true ){
//            dyn_sel.selected_columns.add(i.c_owner);
//            dyn_sel.selected_columns.add(i.c_group);
//            dyn_sel.selected_columns.add(i.c_unixperms);
//            dyn_sel.selected_columns.add(i.c_status);
//        }
//        if( msg.has_description() && msg.description() == true )
//            dyn_sel.selected_columns.add(i.c_description);
//        if( msg.has_name() && msg.name() == true )
//            dyn_sel.selected_columns.add(i.c_name);
//        if( msg.has_shelfs() && msg.shelfs() == true){
//            ///TODO another query for getting shelfs
//        }
//    }
//    else{
//        ///TODO add error resp
//    }

}

void Inventory::handle_modify( const MsgInventoryRequest_Modify &msg)
{
    ///TODO implement
}

void Inventory::handle_remove( const MsgInventoryRequest_Remove &msg)
{
    ///TODO implement
}

void Inventory::handle_addShelf( const MsgInventoryRequest_AddShelf &msg)
{
    ///TODO implement
}


}
}
