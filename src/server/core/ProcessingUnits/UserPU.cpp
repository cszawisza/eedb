#include "UserPU.hpp"
#include "database/UserHelper.hpp"
#include "auth/acl.hpp"
#include "utils/LogUtils.hpp"

#include <Interfaces/UserRequests.hpp>
#include <Validators/UserDataValidator.hpp>

using eedb::utils::PasswordHash;
using uh = eedb::db::UserHelper;
using namespace schema;
using namespace requests::user;

using sqlpp::postgresql::pg_exception;


constexpr users u;

namespace eedb{
namespace pu{


void saveUserActionInDatabase(DB& db, uint64_t uid, const string &action){
    constexpr user_history uh;
    try{
        db(sqlpp::postgresql::insert_into(uh).set(uh.uid = uid, uh.action = action ));
    }
    catch(const pg_exception &e){
        ///TODO proper exception handling
        LOG_DB_ERROR(e);
    }
}

void UserPU::process(IClientRequest *msgReq)
{
    DB db;
    process(db, msgReq);
}

void UserPU::process(DB &db, IClientRequest *msgReq)
{
    Q_ASSERT( msgReq->has_user() );

    auto req = msgReq->user();

    if(user()->isOffline()){
        if ( req->has_add() )
            handle_add(db, req->add() );
        else if( req->has_login() )
            handle_login(db, req->login() );
    }
    else{
        if ( req->has_add() )
            handle_add(db, req->add() );
        else if( req->has_login() )
            handle_login(db, req->login() );
//        else if( )
////        UserReq::ActionCase msgType = req.action_case();
//        switch ( msgType ) {
//        case UserReq::kAdd:
//            handle_add(db, *req.mutable_add() );
//            break;
//        case UserReq::kLogin:
//            handle_login(db, req.login() );
//            break;
//        case UserReq::kLogout:
//            handle_logout(db, req.logout() );
//            break;
//        case UserReq::kGet:
//            handle_get(db, req.get() );
//            break;
//        case UserReq::kRemove:
//            handle_remove(db, req.remove() );
//            break;
//        case UserReq::kModify:
//            handle_modify(db, req.modify() );
//            break;
//        case UserReq::kChangePasswd:
//            handle_changePasswd(db, req.changepasswd());
//            break;
//        case UserReq::ACTION_NOT_SET:
//            // send server error
//            break;
//        }
    }
//    addResponseMessage();
}


void UserPU::addUser(DB &db, const IAdd &msg)
{
    try{
        auto uid = eedb::db::UserHelper::insertUser(db, msg);
//        addErrorCode(UserRes_Reply_UserAddOk );
        saveUserActionInDatabase(db, uid, "register" );
    }
    catch (const pg_exception &e) {
        LOG_DB_EXCEPTION(e)
        if(e.code().pgClass() == "23" ){ //integrity constant validation
//            addErrorCode(UserRes_Reply_UserAlreadyExists);
        }
    }
}

//void UserPU::addErrorCode(UserRes_Reply err)
//{
//    m_response.add_code(err);
//}

//void UserPU::loadUserCache(DB &db, uint64_t uid)
//{
//    constexpr users u;
////    constexpr inventories i;
////    constexpr user_inventories ui;

//    auto udAll = db( uh::selectAll( u.uid == uid ) );
//    const auto &ud = udAll.front();

//    auto basic = user()->mutable_basic();
//    auto stat   = user()->mutable_acl();

//    basic->set_id   ( ud.uid );
//    basic->set_nickname ( ud.name );
//    basic->set_email( ud.email );
//    basic->set_description( ud.description );

//    stat->set_uid(uid);
//    stat->set_group(ud.stat_group);
//    stat->set_status( ud.status );
//    stat->set_unixperms( ud.unixperms );

//    ///TODO get config

////    auto userInventories = db(select(s.uid, s.owner, s.stat_group, s.unixperms, s.status, s.name )
////                           .from(s.inner_join(us)
////                                 .on(us.c_storage_id == s.uid) )
////                           .where(us.user_id == uid ));

//}

//void UserPU::addResponseMessage()
//{
//    add_response()->mutable_userres()->CopyFrom(m_response);
//}

void UserPU::handle_add(DB &db, std::shared_ptr<IAdd> msg)
{
    bool error = false;

    requests::UserAddValidator validator;
//    mailREX.setCaseSensitivity(Qt::CaseInsensitive);
//    mailREX.setPatternSyntax(QRegExp::RegExp);
//    const auto &basic = msg.basic();
//    const auto &det = msg.details();

    if( !validator.hasRequiredFields( *msg ) ){
        ///FIXME
//        addErrorCode( UserRes_Reply_MissingRequiredField);
        error = true;
        return;
    }

    if( !validator.isValid( *msg ) ){
        error = true;
        return;
    }

    if(user()->isOnline()){
        auth::AccesControl stat(user()->id());

        if(stat.checkUserAction<users>("create"))
            addUser(db, *msg);
//        else{
//            sendServerError(pb::Error_AccesDeny);
//        }
    }
    else{
//        if( userExists( db, basic.nickname(), basic.email() ) )
//            addErrorCode(UserRes_Reply_UserAlreadyExists );
//        else
//        {
//            if(msg.has_acl())
//                msg.clear_acl(); // force default values

//            addUser(db, msg);
//        }
    }
}

//void UserPU::goToOnlineState(DB &db, uint64_t uid)
//{
//    saveUserActionInDatabase(db, uid, "login");
//    addErrorCode(UserRes_Reply_LoginPass);

//    user()->goOnline();

//    loadUserCache(db, uid);
//}

void UserPU::handle_login(DB &db, std::shared_ptr<requests::user::ILogin> loginMsg)
{
    if(user()->isOnline()){
        ///FIXME
//        addErrorCode(UserRes_Reply_UserOnline );
    }
    else
    {
        constexpr users u;

        auto prep = db.prepare(uh::selectCredentials(u.name == parameter(u.name) or
                                                     u.uid == parameter(u.uid) or
                                                     u.email == parameter(u.email) ) );
        auto &param = prep.params;
///FIXME
//        if( loginMsg->has_credentials() )
//            param.name = loginMsg.cred().nickname();
//        else if( loginMsg.cred().has_email() )
//            param.email = loginMsg.cred().email();
//        else
//            param.uid = loginMsg.cred().id();

        auto queryRes = db(prep);

//        if ( queryRes.empty() ){
//            addErrorCode(UserRes_Reply_UserDontExist );
//        }
//        else{
//            const auto &row = queryRes.front();

//            string salt = row.salt;
//            string hash = row.password;
//            string hashed_pass = PasswordHash::hashPassword( loginMsg.password(), salt );

//            if( hashed_pass == hash )
//                goToOnlineState(db, row.uid );
//            else{
//                saveUserActionInDatabase(db, row.uid , "wrong password");
//                addErrorCode(UserRes_Reply_LoginDeny );
//            }
//        }
    }
}

//void UserPU::handle_logout(DB &db, const UserReq_Logout &logoutMsg)
//{
//    Q_UNUSED(logoutMsg);
//    saveUserActionInDatabase(db, user()->id(), "logout");
//    user()->goOffLine();
//}

//void UserPU::handle_modify(DB &db, const UserReq_Modify &msg)
//{
//    ///TODO implement
//}

//void UserPU::handle_remove( DB &db, const UserReq_Remove &msg)
//{
//    if(!msg.has_cred()){
//        addErrorCode(UserRes_Reply_MissingRequiredField);
//        return;
//    }

//    ///TODO remove user files/items/history etc
//    ///TODO check if user can remove user with cred
//    auto cred = msg.cred();
//    constexpr users u;
//    auth::AccesControl stat(user()->id());

//    if (stat.checkUserAction<schema::users>("delete", msg.cred().id())){
//        auto query = dynamic_remove(db.connection()).from(u).dynamic_where();
//        if( msg.cred().has_nickname())
//            query.where.add( u.name == msg.cred().nickname() );
//        else if( msg.cred().has_email() )
//            query.where.add( u.email == msg.cred().email() );
//        else
//            query.where.add( u.uid == msg.cred().id() );
//        db(query);
//    }
//    else
//        sendServerError(pb::Error_AccesDeny);
//}

//void UserPU::handle_get(DB &db, const UserReq_Get &getMsg)
//{
//    ///TODO check if can read from users table/user
//}

//void UserPU::handle_changePasswd(DB &db, const UserReq_ChangePasswd &msg)
//{
//    auth::AccesControl stat(user()->id());

//    //    if(msg.has_resetpasswd() && msg.resetpasswd() ){
//    //        ///TODO reset passwd
//    //    }

//    //    else{
//    if(stat.checkUserAction<schema::users>("change_password",msg.uid())){
//        ///TODO check if old pass is same as new
//        ///TODO set new passwd
////        DB db;
////        PasswordHash passwd;
////        passwd.setPassword( msg.new_() );
////        db(update);
//    }
//    else
//        sendServerError(Error_AccesDeny);
//    //    }
//}

//bool UserPU::userExists(DB &db, string name, string email)
//{
//    auto query = db.prepare(uh::selectExists(u.name == parameter(u.name) || u.email == parameter(u.email)));

//    query.params.name = name;
//    query.params.email = email;

//    return db(query).front().exists;
//}

}
}
