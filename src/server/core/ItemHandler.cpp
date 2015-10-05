#include "ItemHandler.hpp"

#include "sql_schema/items.h"
namespace eedb{
namespace handlers{
ItemProcessor::ItemProcessor(){

}

void ItemProcessor::process(ClientRequest &msgReq)
{
    DB db;
    process(db, msgReq);
}

void ItemProcessor::process(DB &db, ClientRequest &msgReq)
{
    // Check if this is the message that handler wants
    Q_ASSERT( msgReq.data_case() == pb::ClientRequest::kItemReqFieldNumber );
    Q_ASSERT( msgReq.has_itemreq() );

    auto req = msgReq.itemreq();

    if(user()->isOffline())
        sendServerError(pb::Error_UserOffilne);

    else{
        ItemRequest::ActionCase msgType = req.action_case();
        switch ( msgType ) {
        case ItemRequest::kAdd:
            handle_add(db, *req.mutable_add() );
            break;
        case ItemRequest::kGet:
//            handle_login(db, req.login() );
            break;
        case ItemRequest::kModify:
//            handle_logout(db, req.logout() );
            break;
        case ItemRequest::kRemove:
//            handle_get(db, req.get() );
            break;
        case UserReq::ACTION_NOT_SET:
            sendServerError(pb::Error_NoActionChoosen);
            break;
        }
    }
}

void ItemProcessor::handle_add(DB &db, ItemRequest_Add &msg)
{
    schema::items it;

    auth::AccesControl stat(user()->id());
    if(stat.checkUserAction<schema::items>(db, "write")){

    } else {
        sendServerError(pb::Error_AccesDeny);
    }
}

}
}
