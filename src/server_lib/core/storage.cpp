#include "storage.h"

#include "sql_schema/t_inventories.h"
#include "sql_schema/t_inventories_history.h"
#include "sql_schema/t_inventories_operations.h"
#include "sql_schema/t_inventories_racks.h"
#include "sql_schema/t_user_inventories.h"

#include <iostream>

schema::t_inventories i;
schema::t_user_inventories ui;

void eedb::handlers::Inventory::process(protbuf::ClientRequest &msg )
{
    // Check if this is the message that handler wants
    Q_ASSERT( msg.data_case() == protbuf::ClientRequest::kMsgInventoryReq );
    Q_ASSERT( msg.has_msginventoryreq() );

    if (!cache()->user().isLogged())
        return;

    auto req = msg.msginventoryreq();

    using inventory::MsgInventoryRequest;
    MsgInventoryRequest::DataCase msgType = req.data_case();
    switch ( msgType ) {
    case MsgInventoryRequest::kAdd:
        handle_add( req.add() );
        break;
    case MsgInventoryRequest::kGet:
        handle_get( req.get() );
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
    case MsgInventoryRequest::DATA_NOT_SET:
        // send server error
        break;
    }
}

void eedb::handlers::Inventory::handle_add(const inventory::MsgInventoryRequest_Add &msgReq)
{
    ///TODO check fields lengths
    ///TODO check if user can add storage
    ///TODO check if acl in msgReq has owner fields (if not, set owner as this user)
    ///TODO add to inventories
    ///TODO link with user

    if(cache()->user().isLogged()){
        insertStorage(msgReq);
    }
    else{
        ///TODO return error: user not logged
    }
}

quint64 eedb::handlers::Inventory::doInsert(DB &db, bool &error, const inventory::MsgInventoryRequest_Add &msgReq)
{
    auto insert = insert_into(i).set(
                i.c_name = parameter(i.c_name),
                i.c_owner = msgReq.acl().owner(),
                i.c_group = msgReq.acl().group(),
                i.c_unixperms = msgReq.acl().unixperms()
            );
    auto query = db.prepare(insert);

    try{
        query.params.c_name = msgReq.name();
    }
    catch( sqlpp::exception e){
        std::cout << e.what();
        error = true;
    }

    ///TODO change to .RETURNING when implemented
    return db.lastInsertId("t_inventories", "c_uid");
}

void eedb::handlers::Inventory::linkInventoryWithUser(DB &db, bool &error, quint64 inventoryId)
{
    try{
        db(insert_into(ui).set(
           ui.c_inventory_id = inventoryId,
           ui.c_user_id = cache()->user().data().id ) );
    }
    catch(sqlpp::exception e){
        std::cout << e.what();
        error = true;
    }
}

void eedb::handlers::Inventory::insertStorage( const inventory::MsgInventoryRequest_Add &msgReq ){
    DB db;

    db.start_transaction();
    bool error = false;

    auto inventoryId = doInsert(db, error, msgReq);
    linkInventoryWithUser(db, error, inventoryId);

    if(error)
        db.rollback_transaction(false);
    else
        db.commit_transaction();
}

void eedb::handlers::Inventory::handle_get(const inventory::MsgInventoryRequest_Get &msg)
{
    ///TODO implement
}

void eedb::handlers::Inventory::handle_modify(const inventory::MsgInventoryRequest_Modify &msg)
{
    ///TODO implement
}

void eedb::handlers::Inventory::handle_remove(const inventory::MsgInventoryRequest_Remove &msg)
{
    ///TODO implement
}

void eedb::handlers::Inventory::handle_addShelf(const inventory::MsgInventoryRequest_AddShelf &msg)
{
    ///TODO implement
}
