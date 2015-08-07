#include "inventory.hpp"

#include "sql_schema/t_inventories.h"
#include "sql_schema/t_inventories_history.h"
#include "sql_schema/t_inventories_operations.h"
#include "sql_schema/t_user_inventories.h"
#include "sql_schema/t_shelfs.h"

#include "sqlpp11/sqlpp11.h"

#include <iostream>

#include "utils/unixPerms.hpp"

#include "database/InventoryHelper.hpp"

schema::t_inventories i;
schema::t_user_inventories u_i;

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
        handle_addShelf(db, *req.mutable_addshelf() );
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
    }
}

void Inventory::handle_get( DB &db, MsgInventoryRequest_Get &msg)
{
    auto where = msg.where().cred_case();

    uint64_t uid = user()->id() ;
    auth::AccesControl acl(uid);
    const int oid = msg.id();

    auto select = dynamic_select(db.connection())
            .dynamic_columns(sqlpp::all_of(i))
            .dynamic_from(i)
            .extra_tables(u_i,i)
            .dynamic_where();

    switch (where) {
    case MsgInventoryRequest_Get_Where::kUserId:{
        select.where.add( u_i.c_user_id == msg.where().user_id() );
        select.from.add(u_i);
        auto val = db(select);
    }
        break;
    case MsgInventoryRequest_Get_Where::kInventoryId:{
        // get inventory with given ID
        if(! db(sqlpp::select(sqlpp::exists(sqlpp::select(i.c_uid).from(i).where(i.c_uid == msg.where().inventory_id() )))).front().exists){
            ///TODO return information that ID dont exist in db
            return;
        } else {
            if(!acl.checkUserAction<t_inventories>("read", msg.where().inventory_id())){
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

void Inventory::handle_modify( const MsgInventoryRequest_Modify &msg)
{
    ///TODO implement
}

void Inventory::handle_remove( const MsgInventoryRequest_Remove &msg)
{
    ///TODO implement
}

void Inventory::handle_addShelf(DB &db, MsgInventoryRequest_AddShelf &msg)
{
    auth::AccesControl accessControl( user()->id() );

    if( accessControl.checkUserAction<t_shelfs>(db, "write")){
        auto acl = msg.mutable_acl();
        acl->set_owner( user()->id( ));
        acl->set_group( auth::GROUP_inventories );
        acl->set_unixperms( UnixPermissions( {7,0,0} ).toInteger() );
        acl->set_status( auth::State_Normal );

        try{
            InventoryHelper::insertShelf(db, msg);
            addErrorCode(MsgInventoryResponse_Error_No_Error);
        }
        catch(const pg_exception &e){
            ///TODO proper exception handling
            std::cout << e.what();
            addErrorCode(MsgInventoryResponse_Error_DbAccesError);
        }
    }
    else {
        sendAccesDeny();
    }
}
}
}
