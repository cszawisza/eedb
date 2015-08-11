#include "category.hpp"
#include "database/idatabase.h"

void eedb::handlers::Category::process(pb::ClientRequest &msgReq)
{
    DB db;
    process(db, msgReq);
}

void eedb::handlers::Category::process(DB &db, pb::ClientRequest &msgReq)
{
    // Check if this is the message that handler wants
    Q_ASSERT( msgReq.data_case() == pb::ClientRequest::kCategoryReqFieldNumber );
    Q_ASSERT( msgReq.has_userreq() );

    auto req = msgReq.categoryreq();

    if(user()->isOffline()){
        sendAccesDeny();
        return;
    }
    else{
CategoryReq::ActionCase msgType = req.action_case();
        switch ( msgType ) {
        case CategoryReq::kAdd:
            break;
        case CategoryReq::kRemove:
            break;
        case CategoryReq::kModify:
            break;
        case CategoryReq::kGet:
            break;
        case CategoryReq::kModifyParameters:
            break;
        case CategoryReq::ACTION_NOT_SET:
            // send server error
            break;
        }
    }
}
