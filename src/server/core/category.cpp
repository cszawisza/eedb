#include "category.hpp"
#include "database/idatabase.h"

#include "sql_schema/t_categories.h"
#include "sql_schema/t_category_files.h"

#include "auth/acl.hpp"

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
        auto prep_insert = insert_into(cat).set(
                    cat.c_name = parameter(cat.c_name),
                    cat.c_description = parameter(cat.c_description ),
                    cat.c_parent_category_id = msg.parent_id()
                );

        auto p = db.prepare(prep_insert);

        p.params.c_name = msg.name();
        if( msg.has_description() )
            p.params.c_description = msg.description();

        db(p);

        auto response = add_response()->mutable_categoryres();
        response->set_code(CategoryRes_Replay_OK);
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
