#include "CategoryPU.hpp"
#include "database/idatabase.h"
#include "database/CategoryHelper.hpp"
#include "auth/implementedaction.hpp"
#include "auth/acl.hpp"
#include "utils/sqlpp_helper.hpp"
#include "utils/LogUtils.hpp"
#include "utils/unixPerms.hpp"

#include "Interfaces/CategoryRequests.hpp"
#include "Interfaces/CategoryResponses.hpp"

using CH = eedb::db::CategoryHelper;
using sqlpp::fieldName;

namespace eedb{
namespace pu{

void CategoryPU::process(IClientRequest *msgReq)
{
    DB db;
    process(db, msgReq);
}

void CategoryPU::process(DB &db, IClientRequest *msgReq)
{
    // Check if this is the message that handler wants
    Q_ASSERT( msgReq->has_category() );

    requests::ICategory *req = msgReq->category();

    if(user()->isOffline()){
        sendServerError( IServerResponse::Error_UserOfline );
        return;
    }
    else{
        if(req->has_add())
            handle_add(db, req->get_add() );

//        auto msgType = req.action_case();
//        switch ( msgType ) {
//        case CategoryReq::kAdd:
//            break;
//        case CategoryReq::kRemove:
//            break;
//        case CategoryReq::kModify:
//            break;
//        case CategoryReq::kGet:
//            handle_get(db, *req.mutable_get() );
//            break;
//        case CategoryReq::kModifyParameters:
//            break;
//        case CategoryReq::ACTION_NOT_SET:
//            // send server error
//            break;
//        }
    }
}

void CategoryPU::handle_add(DB &db, const requests::category::IAdd &msg)
{
    static constexpr schema::categories cat;
    auth::AccesControl stat( user()->id() );

    ///TODO add name chacking
    if( !msg.has_name() ){
        response()->category()->add()->set_code(responses::category::IAdd::Error_NameMissing );
        return;
    }
    if( !msg.has_parentId() ){
        ///FIXME
//        add_response()->mutable_categoryres()->set_code(CategoryRes_Replay_MissingParentId);
        return;
    }

    if(stat.checkUserAction<schema::categories>(db, "write") ){
//         treat id = =0 as root category
        if(!msg.has_parentId() || msg.get_parentId() == 0 );
//            msg.set_parentId( CH::rootCategoryId(db).get_value_or(0) );

        auto res = response()->category();
        auto prepare = db.prepare(CH::insert_into().set(
                                      cat.name = parameter(cat.name),
                                      cat.description = parameter(cat.description ),
                                      cat.owner = user()->id(),
                                      cat.stat_group = (int)auth::GROUP_categories,
                                      cat.unixperms = UnixPermissions({7,4,4}).toInteger(),
                                      cat.parent_category_id = msg.get_parentId()
                ).returning(cat.uid));

        prepare.params.name = msg.get_name();
        if( msg.has_description() )
            prepare.params.description = msg.get_description();

        try{
            auto result = db(prepare);

//            res->add()->set_code(0);
//            if(msg.has_parentId() && msg.returningid())
//                response->set_id(result.front().uid);
        }
        catch(sqlpp::postgresql::pg_exception e){
//            if(e.code().pgClass() == "23") // Unique key validation
//                response->set_code(CategoryRes_Replay_CategoryExists); // occour when category exists or no parent id
//            else{
//                LOG_DB_EXCEPTION(e);
//            }
        }
    }
    else{
        sendServerError( IServerResponse::Error_AccesDeny );
    }
}

void CategoryPU::handle_get(DB &db, const requests::category::IGet &msg)
{
    static constexpr schema::categories cat;
    auth::AccesControl stat( user()->id() );

    if(stat.checkUserAction<schema::categories>(db, "read") ){
        auto s = dynamic_select(db.connection()).dynamic_columns().dynamic_from(cat).dynamic_where();

        if(msg.has_requestedUid())
            s.selected_columns.add(cat.uid);
        if(msg.has_requestedName())
            s.selected_columns.add(cat.name);
        if(msg.has_requestedParentUid())
            s.selected_columns.add(cat.parent_category_id);

        if(msg.get_criteria().has_requested_all())
            s.where.add(cat.status == static_cast<int>(auth::State_Normal));

        auto results = db(s);
///FIXME
//        using namespace schema::categories_;
//        for(const auto &row:results){
//            auto cres = add_response()->mutable_categoryres();
//            if(msg.has_requestedUid())
//                cres->set_id(boost::lexical_cast<uint64_t>(row.at(fieldName<Uid>())));
//            if(msg.has_get_name() && msg.get_name())
//                cres->set_name(row.at(fieldName<Name>()));
//            if(msg.has_get_description() && msg.get_description())
//                cres->set_description(row.at(fieldName<Description>()));
//        }
    }
    else{
        ///FIXME
//        sendServerError( pb::Error_AccesDeny );
    }
}

}
}
