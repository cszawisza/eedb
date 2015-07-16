#include "inventory.hpp"

#include "sql_schema/t_inventories.h"
#include "sql_schema/t_inventories_history.h"
#include "sql_schema/t_inventories_operations.h"
#include "sql_schema/t_inventories_shelfs.h"
#include "sql_schema/t_user_inventories.h"
#include "sql_schema/t_shelfs.h"

#include "sqlpp11/sqlpp11.h"

#include <iostream>

#include "utils/unixPerms.hpp"

schema::t_inventories i;
schema::t_user_inventories u_i;
schema::t_inventories_shelfs i_s;

using namespace pb;
using namespace schema;

namespace eedb{
namespace handlers{

void Inventory::process(DB &db, ClientRequest &msg)
{
    m_response.Clear();
    // Check if this is the message that handler wants
    Q_ASSERT( msg.data_case() == pb::ClientRequest::kMsgInventoryReq );
    Q_ASSERT( msg.has_msginventoryreq() );

    if (!user()->isOnline()){
//        addErrorCode(  );
        return;
    }

    auto req = msg.msginventoryreq();

    MsgInventoryRequest::ActionCase msgType = req.action_case();
    switch ( msgType ) {
    case MsgInventoryRequest::kAdd:
        handle_add( db, req.add() );
        break;
    case MsgInventoryRequest::kGet:
        handle_get( db, req.get() );
        break;
    case MsgInventoryRequest::kRemove:
        handle_remove( req.remove() );
        break;
    case MsgInventoryRequest::kModify:
        handle_modify( req.modify() );
        break;
    case MsgInventoryRequest::kAddShelf:
        handle_addShelf( req.addshelf() );
        break;
    case MsgInventoryRequest::ACTION_NOT_SET:
        //addResp(true, Error_NoActionChoosen);
        break;
    }

    addResponse(m_response);
}

void Inventory::process(pb::ClientRequest &msg )
{
    DB db;
    ///TODO transaction managment
    process(db, msg);
}

void Inventory::handle_add( DB &db, const MsgInventoryRequest_Add &msg)
{
    bool error = false;
    if(msg.name().length() > 250 ){
        error = true;
        addErrorCode( MsgInventoryResponse_Error_NameToLong);
    }
    if(msg.name().length() < 1 ){
        error = true;
        addErrorCode( MsgInventoryResponse_Error_NameEmpty);
    }
    if(msg.description().length() > 100000 ){
        error = true;
        addErrorCode( MsgInventoryResponse_Error_DescriptionToLong );
    }

    if(error)
        return;

    try{
//        db.start_transaction();
        insertInventory(db, msg);
//        db.commit_transaction();
        addErrorCode(MsgInventoryResponse_Error_No_Error);
    }
    catch(sqlpp::exception){
//        db.rollback_transaction(false);
        addErrorCode(MsgInventoryResponse_Error_DbAccesError);
    }
}

quint64 Inventory::doInsertInventory(DB &db, const MsgInventoryRequest_Add &msgReq)
{
    auto insert = insert_into(i).set(
                i.c_name = parameter(i.c_name),
                i.c_owner = user()->id(),
                i.c_group = (int)auth::GROUP_inventories,
                i.c_unixperms = UnixPermissions("rwdr-----").toInteger()
            );
    auto query = db.prepare(insert);

    query.params.c_name = msgReq.name();
    db(query);

    ///TODO change to .RETURNING when implemented
    return db.lastInsertId( sqlpp::tableName<t_acl>(), "c_uid" );
}

void Inventory::linkInventoryWithUser(DB &db, quint64 inventoryId)
{
        db(insert_into(u_i).set(
           u_i.c_inventory_id = inventoryId,
           u_i.c_user_id = user()->id() ) );
}

void Inventory::insertInventory(DB &db, const MsgInventoryRequest_Add &msg ){
    constexpr schema::t_shelfs s;
    constexpr schema::t_inventories_shelfs is;

    auth::AccesControl acl( user()->id() );

    if( acl.checkUserAction<t_inventories>(db, "write")){
        quint64 inventoryId = doInsertInventory(db, msg);
        linkInventoryWithUser(db,  inventoryId);

        if(msg.shelfs_size()){
            ///TODO change to returning when avalible
            if( acl.checkUserAction<t_shelfs>(db, "write")){
                ///TODO use prepared statements
                auto insert_statement = insert_into(s).columns(
                            s.c_name,
                            s.c_owner,
                            s.c_description
                            );

                for( const auto &shelf : msg.shelfs() ){
                    insert_statement.values.add(
                                s.c_name = shelf.name(),
                                s.c_owner = user()->id(),
                                s.c_description = shelf.description() );
                    db(insert_statement);
                    auto shelfId = db.lastInsertId(sqlpp::tableName<schema::t_acl>(),"c_uid" );
                    db(insert_into(is).set(is.c_inventory_id = inventoryId, is.c_shelf = shelfId )  );
                }
            }
            else {
                sendAccesDeny();
            }
        }
    }
}

void Inventory::handle_get( DB &db, const MsgInventoryRequest_Get &msg)
{
    auto &where = msg.where();

    quint64 uid = user()->id() ;
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
        if(! db(sqlpp::select(exists(sqlpp::select(i.c_uid).from(i).where(i.c_uid == where.inventory_id() )))).front().exists){
            ///TODO return information that ID dont exist in db
            return;
        } else {
            if(!acl.checkUserAction<t_inventories>("read", where.inventory_id() )){
                sendAccesDeny();
                return;
            }
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
