#include "ItemPU.hpp"
#include "item.pb.h"
#include <sqlpp11/sqlpp11.h>
#include <sqlpp11/postgresql/insert.h>
#include "sql_schema/items.h"
#include "sql_schema/parameters.h"

#include <QJsonObject>
#include <QJsonDocument>

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
        case ItemReq::kAdd:
            handle_add(db, *req.mutable_add() );
            break;
        case ItemReq::kGet:
//            handle_login(db, req.login() );
            break;
        case ItemReq::kModify:
//            handle_logout(db, req.logout() );
            break;
        case ItemReq::kRemove:
//            handle_get(db, req.get() );
            break;
        case UserReq::ACTION_NOT_SET:
            sendServerError(pb::Error_NoActionChoosen);
            break;
        }
    }
}

void ItemPU::handle_add(DB &db, ItemReq_Add &msg)
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


void ItemPU::run_saveItemInDb(DB &db, ItemReq_Add &msg)
{
    //check parameters

    QJsonObject params;

    if(msg.parameters_size() > 0){
        static constexpr schema::parameters p;
        std::vector<quint64> parametersIds;
        for(const auto &parameter:msg.parameters())
            parametersIds.push_back( parameter.id() );

        // check is all parameters are avalible in database
        ///TODO check if pointed value exists
        bool allAvalible = db( select(count(p.uid))
                               .from(p)
                               .where(p.uid.in(sqlpp::value_list(parametersIds))))
                .front().count == parametersIds.size();

        if(!allAvalible){
            add_response()->mutable_itemres()->set_code(pb::ItemResponse_Replay_ParameterDontExists);
            return;
        }

        for(const pb::ParameterValue &parameter:msg.parameters()){
            params.insert("id", (qint64)parameter.id() );
            if(parameter.has_stored_value() )
                params.insert("storedValue", "");
            else
                params.insert("pointedValue", (qint64)parameter.pointed_value() );
        }
    }

    auto res = add_response()->mutable_itemres();
    auto prep = db.prepare(sqlpp::postgresql::insert_into(i).set(
                               i.name = parameter(i.name),
                               i.category_id = msg.category_id(),
                               i.symbol = parameter(i.symbol),
                               i.owner = user()->id(),
                               i.description = parameter(i.description),
                               i.params = parameter(i.params)
            ).returning(i.uid) );

    prep.params.name = msg.name();
    prep.params.symbol = msg.symbol();
    prep.params.params = QJsonDocument(params).toJson().toStdString();

    if(msg.has_description() && !msg.description().empty())
        prep.params.description = msg.description();

    auto return_value = db(prep);

    if(msg.has_returning_id() && msg.returning_id())
        res->set_id(return_value.front().uid);

    res->set_code(ItemResponse_Replay_OK);
}

}
}
