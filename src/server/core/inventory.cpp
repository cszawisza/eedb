#include "inventory.hpp"

#include <iostream>

#include "utils/unixPerms.hpp"
#include "database/InventoryHelper.hpp"
#include "utils/LogUtils.hpp"

schema::inventories i;
schema::user_inventories u_i;

using namespace pb;
using namespace schema;
using eedb::db::InventoryHelper;
using sqlpp::postgresql::pg_exception;

namespace eedb{
namespace pu{

void Inventory::process(DB &db, ClientRequest &msg)
{
    // Check if this is the message that handler wants
    Q_ASSERT( msg.data_case() == pb::ClientRequest::kMsgInventoryReq );
    Q_ASSERT( msg.has_msginventoryreq() );

    if (!user()->isOnline()){
        sendServerError(pb::Error_AccesDeny);
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
}

void Inventory::process(pb::ClientRequest &msg )
{
    DB db;
    process(db, msg);
}

void Inventory::handle_add( DB &db, MsgInventoryRequest_Add &msg)
{
    auto res = add_response();
    bool error = false;
    if(msg.name().length() > 250 ){
        error = true;
        addErrorCode( MsgInventoryResponse_Error_NameToLong, res);
    }
    if(msg.name().length() < 1 ){
        error = true;
        addErrorCode( MsgInventoryResponse_Error_NameEmpty, res);
    }
    if(msg.description().length() > 100000 ){
        error = true;
        addErrorCode( MsgInventoryResponse_Error_DescriptionToLong, res);
    }

    if(error)
        return;

    try{
        insertInventory(db, msg);
        addErrorCode(MsgInventoryResponse_Error_No_Error, res);
    }
    catch(const pg_exception &e){
        LOG_DB_ERROR(e);
        addErrorCode(MsgInventoryResponse_Error_DbAccesError, res);
    }
}

void Inventory::insertInventory(DB &db, MsgInventoryRequest_Add &msg ){
    auth::AccesControl accessControl( user()->id() );

    if( accessControl.checkUserAction<inventories>(db, "write")){
        msg.mutable_acl()->set_owner( user()->id( ));

        InventoryHelper::insertInventory(db, msg);
        InventoryHelper::linkWithUser(db, user(),  msg.acl().uid());
    }
}

void Inventory::handle_get( DB &db, MsgInventoryRequest_Get &msg)
{
    auto where = msg.where().cred_case();

    uint64_t uid = user()->id() ;
    auth::AccesControl stat(uid);

    auto select = dynamic_select(db.connection())
            .dynamic_columns(sqlpp::all_of(i))
            .dynamic_from(i)
            .extra_tables(u_i,i)
            .dynamic_where();

    switch (where) {
    case MsgInventoryRequest_Get_Where::kUserId:{
        select.where.add( u_i.user_id == msg.where().user_id() );
        select.from.add(u_i);

        auto result = db(select);

        for( const auto &row : result){
            auto res = add_response()->mutable_msginventoryres();
            res->set_id(row.uid);
            res->set_name(row.name);
            res->set_description(row.description);
        }
    }

        break;
    case MsgInventoryRequest_Get_Where::kInventoryId:{
        // get inventory with given ID
        if(! db(sqlpp::select(sqlpp::exists(sqlpp::select(i.uid).from(i).where(i.uid == msg.where().inventory_id() )))).front().exists){
            ///TODO return information that ID dont exist in db
            return;
        } else {
            if(!stat.checkUserAction<inventories>("read", msg.where().inventory_id())){
                sendServerError(pb::Error_AccesDeny);
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
    auto res = add_response();

    auth::AccesControl accessControl( user()->id() );

    if( accessControl.checkUserAction<shelfs>(db, "write")){
        auto stat = msg.mutable_acl();
        stat->set_owner( user()->id( ));
        stat->set_group( auth::GROUP_inventories );
        stat->set_unixperms( UnixPermissions( {7,0,0} ).toInteger() );
        stat->set_status( auth::State_Normal );

        try{
            InventoryHelper::insertShelf(db, msg);
            addErrorCode(MsgInventoryResponse_Error_No_Error, res);
        }
        catch(const pg_exception &e){
            LOG_DB_EXCEPTION(e);
            addErrorCode(MsgInventoryResponse_Error_DbAccesError, res);
        }
    }
    else {
        sendServerError(pb::Error_AccesDeny);
    }
}
}
}
