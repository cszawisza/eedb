#include "ItemPU.hpp"
#include "item.pb.h"
#include <sqlpp11/sqlpp11.h>
#include <sqlpp11/postgresql/insert.h>
#include "sql_schema/items.h"

using namespace pb;

namespace eedb{
namespace pu{

constexpr schema::items i;

ItemPU::ItemPU(){

}

void ItemPU::process(ClientRequest &msgReq)
{
    DB db;
    process(db, msgReq);
}

void ItemPU::process(DB &db, ClientRequest &msgReq)
{
    // Check if this is the message that handler wants
    Q_ASSERT( msgReq.data_case() == pb::ClientRequest::kItemReqFieldNumber );
    Q_ASSERT( msgReq.has_itemreq() );

    auto req = msgReq.itemreq();

    if(user()->isOffline())
        sendServerError(pb::Error_UserOffilne);

    else{
        auto msgType = req.action_case();
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

void ItemPU::handle_add(DB &db, ItemRequest_Add &msg)
{
    constexpr schema::items it;

    auth::AccesControl stat(user()->id());

    bool allow = false;
    if(msg.has_is_private() && msg.is_private())
        allow = stat.checkUserAction<schema::items>(db, "add_private_item");
    else
        allow = stat.checkUserAction<schema::items>(db, "add_public_item");

    if(allow){
        run_saveItemInDb(db, msg);
    } else {
        sendServerError(pb::Error_AccesDeny);
    }
}

void ItemPU::run_saveItemInDb(DB &db, ItemRequest_Add &msg)
{
    auto res = add_response()->mutable_itemres();
    auto prep = db.prepare(sqlpp::postgresql::insert_into(i).set(
                               i.name = parameter(i.name),
                               i.category_id = msg.category_id(),
                               i.symbol = parameter(i.symbol),
                               i.owner = user()->id(),
                               i.description = parameter(i.description),
                               i.parameters = "{}"
            ).returning(i.uid) );

    prep.params.name = msg.name();
    prep.params.symbol = msg.symbol();

    if(msg.has_description() && !msg.description().empty())
        prep.params.description = msg.description();

    auto return_value = db(prep);

    if(msg.has_returning_id() && msg.returning_id())
        res->set_id(return_value.front().uid);

    res->set_code(ItemResponse_Replay_OK);
}

}
}
