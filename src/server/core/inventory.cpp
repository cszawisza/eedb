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

#include "database/InventoryHelper.hpp"

schema::t_inventories i;
schema::t_user_inventories u_i;
schema::t_inventories_shelfs i_s;

using namespace pb;
using namespace schema;
using eedb::db::InventoryHelper;
using sqlpp::postgresql::pg_exception;

namespace eedb{
namespace handlers{

void Inventory::process(DB &db, ClientRequest &msg)
{
    m_response.Clear();
    // Check if this is the message that handler wants
    Q_ASSERT( msg.data_case() == pb::ClientRequest::kMsgInventoryReq );
    Q_ASSERT( msg.has_msginventoryreq() );

    if (!user()->isOnline()){
        sendAccesDeny();
        return;
    }

    auto req = msg.msginventoryreq();

    MsgInventoryRequest::ActionCase msgType = req.action_case();
    switch ( msgType ) {
    case MsgInventoryRequest::kAdd:
        handle_add( db, *req.mutable_add() );
        break;
    case MsgInventoryRequest::kGet:
        handle_get( db, *req.mutable_get() );
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
    process(db, msg);
}

void Inventory::handle_add( DB &db, MsgInventoryRequest_Add &msg)
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
        insertInventory(db, msg);
        addErrorCode(MsgInventoryResponse_Error_No_Error);
    }
    catch(const pg_exception &e){
        ///TODO proper exception handling
        std::cout << e.what();
        addErrorCode(MsgInventoryResponse_Error_DbAccesError);
    }
}

void Inventory::insertInventory(DB &db, MsgInventoryRequest_Add &msg ){
    auth::AccesControl accessControl( user()->id() );

    if( accessControl.checkUserAction<t_inventories>(db, "write")){
        msg.mutable_acl()->set_owner( user()->id( ));

        InventoryHelper::insertInventory(db, msg);
        InventoryHelper::linkWithUser(db, user(),  msg.acl().uid());

        for( int i=0;i<msg.shelfs_size();i++){
            auto shelf = msg.mutable_shelfs(i);
            shelf->set_inventory_id(msg.acl().uid());
            auto acl = shelf->mutable_acl();

            acl->set_owner( user()->id() );
            acl->set_unixperms( UnixPermissions( {7,0,0} ).toInteger() );
        }

        if( msg.shelfs_size() && accessControl.checkUserAction<t_shelfs>(db, "write")){
            InventoryHelper::addShelfs(db, msg.shelfs());
        }
        else {
            sendAccesDeny();
        }

    }
}

void Inventory::handle_get( DB &db, MsgInventoryRequest_Get &msg)
{
    auto where = msg.Where_case();

    quint64 uid = user()->id() ;
    auth::AccesControl acl(uid);
    const int oid = msg.id();

    switch (where) {
    case MsgInventoryRequest_Get::kUserId:{
        // get all user inventories
        auto dyn_sel = dynamic_select( db.connection())
                .dynamic_columns(i.c_uid)
                .from(i)
                .dynamic_where( i.c_uid == oid );

        if( msg.has_name() && msg.name())
            dyn_sel.selected_columns.add(i.c_name);
        if( msg.has_description() && msg.description())
            dyn_sel.selected_columns.add(i.c_description);
        if( msg.has_acl() && msg.acl()){
            dyn_sel.selected_columns.add(i.c_owner);
            dyn_sel.selected_columns.add(i.c_group);
            dyn_sel.selected_columns.add(i.c_unixperms);
            dyn_sel.selected_columns.add(i.c_status);
        }
    }
        break;
    case MsgInventoryRequest_Get::kInventoryId:{
        // get inventory with given ID
        if(! db(sqlpp::select(sqlpp::exists(sqlpp::select(i.c_uid).from(i).where(i.c_uid == msg.inventory_id() )))).front().exists){
            ///TODO return information that ID dont exist in db
            return;
        } else {
            if(!acl.checkUserAction<t_inventories>("read", msg.inventory_id())){
                sendAccesDeny();
                return;
            }
        }
    }
        break;
    default:
        break;
    }

    ///TODO get all storage shelfs
}
//    else if(where.has_inventory_id() ){

//    }

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
