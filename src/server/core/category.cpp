#include "category.hpp"
#include "database/idatabase.h"

#include "database/CategoryHelper.hpp"
#include "auth/implementedaction.hpp"
#include "auth/acl.hpp"
#include "utils/sqlpp_helper.hpp"
#include "utils/LogUtils.hpp"
using CH = eedb::db::CategoryHelper;
using sqlpp::fieldName;
namespace eedb{
namespace handlers{

void Category::process(ClientRequest &msgReq)
{
    DB db;
    process(db, msgReq);
}

void Category::process(DB &db, pb::ClientRequest &msgReq)
{
    // Check if this is the message that handler wants
    Q_ASSERT( msgReq.data_case() == pb::ClientRequest::kCategoryReqFieldNumber );
    Q_ASSERT( msgReq.has_categoryreq() );

    auto req = msgReq.categoryreq();

    if(user()->isOffline()){
        sendServerError(pb::Error_UserOffilne);
        return;
    }
    else{
        CategoryReq::ActionCase msgType = req.action_case();
        switch ( msgType ) {
        case CategoryReq::kAdd:
            handle_add(db, *req.mutable_add() );
            break;
        case CategoryReq::kRemove:
            break;
        case CategoryReq::kModify:
            break;
        case CategoryReq::kGet:
            handle_get(db, *req.mutable_get() );
            break;
        case CategoryReq::kModifyParameters:
            break;
        case CategoryReq::ACTION_NOT_SET:
            // send server error
            break;
        }
    }
}

void Category::handle_add(DB &db, CategoryReq_Add &msg)
{
    static constexpr schema::categories cat;
    auth::AccesControl stat( user().data()->id() );

    ///TODO add name chacking
    if( !msg.has_name() ){
        add_response()->mutable_categoryres()->set_code(CategoryRes_Replay_MissingName);
        return;
    }
    if( !msg.has_parent_id() ){
        add_response()->mutable_categoryres()->set_code(CategoryRes_Replay_MissingParentId);
        return;
    }

    if(stat.checkUserAction<schema::categories>(db, "write") ){
        auto response = add_response()->mutable_categoryres();
        auto prepare = db.prepare(CH::insert_into().set(
                                      cat.name = parameter(cat.name),
                                      cat.description = parameter(cat.description ),
                                      cat.parent_category_id = msg.parent_id()
                ).returning(cat.uid));

        prepare.params.name = msg.name();
        if( msg.has_description() )
            prepare.params.description = msg.description();

        try{
            auto result = db(prepare);

            response->set_code(CategoryRes_Replay_AddSuccesful);
            if(msg.has_returningid() && msg.returningid())
                response->set_id(result.front().uid);
        }
        catch(sqlpp::postgresql::pg_exception e){
            if(e.code().pgClass() == "23") // Unique key validation
                response->set_code(CategoryRes_Replay_CategoryExists); // occour when category exists
            else{
                LOG_DB_EXCEPTION(e);
            }
        }
    }
    else{
        sendServerError(pb::Error_AccesDeny);
    }
}

void Category::handle_get(DB &db, CategoryReq_Get &msg)
{
    static constexpr schema::categories cat;
    auth::AccesControl stat( user().data()->id() );

    if(stat.checkUserAction<schema::categories>(db, "read") ){
        auto s = dynamic_select(db.connection()).dynamic_columns().dynamic_from(cat).dynamic_where();

        if(msg.has_get_ids() && msg.get_ids())
            s.selected_columns.add(cat.uid);
        if(msg.has_get_name() && msg.get_name())
            s.selected_columns.add(cat.name);
        if(msg.has_get_description() && msg.get_description())
            s.selected_columns.add(cat.description);

        if(msg.where().all_groups())
            s.where.add(cat.status == static_cast<int>(auth::State_Normal));

        auto results = db(s);

        using namespace schema::categories_;
        for(const auto &row:results){
            auto cres = add_response()->mutable_categoryres();
            if(msg.has_get_ids() && msg.get_ids())
                cres->set_id(boost::lexical_cast<uint64_t>(row.at(fieldName<Uid>())));
            if(msg.has_get_name() && msg.get_name())
                cres->set_name(row.at(fieldName<Name>()));
            if(msg.has_get_description() && msg.get_description())
                cres->set_description(row.at(fieldName<Description>()));
        }
    }
    else{
        sendServerError( pb::Error_AccesDeny );
    }
}

}
}
