#include "category.hpp"
#include "database/idatabase.h"

#include "database/CategoryHelper.hpp"

#include "auth/acl.hpp"

#include "utils/LogUtils.hpp"
using CH = eedb::db::CategoryHelper;
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
        sendAccesDeny();
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
    static constexpr schema::t_categories cat;
    auth::AccesControl acl( user().data()->id() );

    ///TODO add name chacking
    if( !msg.has_name() ){
        add_response()->mutable_categoryres()->set_code(CategoryRes_Replay_MissingName);
        return;
    }
    if( !msg.has_parent_id() ){
        add_response()->mutable_categoryres()->set_code(CategoryRes_Replay_MissingParentId);
        return;
    }

    if(acl.checkUserAction<schema::t_categories>(db, "write") ){
        auto response = add_response()->mutable_categoryres();
        auto prepare = db.prepare(CH::insert_into().set(
                                      cat.c_name = parameter(cat.c_name),
                                      cat.c_description = parameter(cat.c_description ),
                                      cat.c_parent_category_id = msg.parent_id()
                ).returning(cat.c_uid));

        prepare.params.c_name = msg.name();
        if( msg.has_description() )
            prepare.params.c_description = msg.description();

        try{
            auto result = db(prepare);

            response->set_code(CategoryRes_Replay_AddSuccesful);
            if(msg.has_returningid() && msg.returningid())
                response->set_id(result.front().c_uid);
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
        sendAccesDeny();
    }
}

void Category::handle_get(DB &db, CategoryReq_Get &msg)
{

}

}
}
