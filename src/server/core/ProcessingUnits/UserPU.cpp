#include "UserPU.hpp"
#include "database/UserHelper.hpp"
#include "auth/acl.hpp"
#include "utils/LogUtils.hpp"

#include <Interfaces/UserRequests.hpp>
#include <Interfaces/UserResponses.hpp>

#include <Validators/UserDataValidator.hpp>

#include <QFlags>

using eedb::utils::PasswordHash;
using uh = eedb::db::UserHelper;

using namespace schema;

using sqlpp::postgresql::pg_exception;

namespace req = requests::user;
namespace res = responses::user;

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
            handle_add(db, req->get_add() );
        else if( req->has_login() )
            handle_login(db, req->get_login() );
    }
    else{
        if ( req->has_add() )
            handle_add(db, req->get_add() );
        else if( req->has_login() )
            handle_login(db, req->get_login() );
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


void UserPU::addUser(DB &db, const req::IAdd &msg)
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

void UserPU::raise_addErrorCode(int err)
{
    auto flags = response()->user()->add()->get_error_code();
    flags |= QFlag(err);
    response()->user()->add()->set_error(flags);
}

void UserPU::raise_loginError(int err)
{
    res::ILogin::LoginErrors flags = response()->user()->login()->get_error_code();
    flags |= QFlag(err);
    response()->user()->login()->set_error(flags);
}

void UserPU::loadUserCache(DB &db, uint64_t uid)
{
//    constexpr users u;
//    constexpr inventories i;
//    constexpr user_inventories ui;

//    auto udAll = db( uh::selectAll( u.uid == uid ) );
//    const auto &ud = udAll.front();
///NOTE do i really need stored user information? UID only is not enougt?

    user()->setUid(uid);
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

    ///TODO get config

//    auto userInventories = db(select(s.uid, s.owner, s.stat_group, s.unixperms, s.status, s.name )
//                           .from(s.inner_join(us)
//                                 .on(us.c_storage_id == s.uid) )
//                           .where(us.user_id == uid ));

}

//void UserPU::addResponseMessage()
//{
//    add_response()->mutable_userres()->CopyFrom(m_response);
//}

void UserPU::handle_add(DB &db,const req::IAdd &msg)
{
    bool error = false;

    requests::UserAddValidator validator;

    if( !validator.hasRequiredFields( msg ) ){
        raise_addErrorCode( res::IAdd::Error_MissingRequiredFields );
        error = true;
        return;
    }

    if( !validator.isValid( msg ) ){
        error = true;
        return;
    }

    if(user()->isOnline()){
        auth::AccesControl stat(user()->id());

        if(stat.checkUserAction<users>("create"))
            addUser(db, msg);
        else{
            sendServerError( IServerResponse::Error_AccesDeny);
        }
    }
    else{
        if( userExists( db, msg.get_nickname(), msg.get_email() ) ){
            raise_addErrorCode(res::IAdd::Error_UserExists );
        }
        else
        {
            //            if(msg.has_acl())
            //                msg.clear_acl(); // force default values
            addUser(db, msg);
        }
    }
}

void UserPU::goToOnlineState(DB &db, uint64_t uid)
{
    saveUserActionInDatabase(db, uid, "login");
    ///TODO change to something else
    raise_loginError(0);

    user()->goOnline();

    loadUserCache(db, uid);
}

void UserPU::handle_login(DB &db, const req::ILogin &loginMsg)
{
    if(user()->isOnline()){
        raise_loginError(res::ILogin::Error_UserOnline );
    }
    else
    {
        Q_ASSERT(loginMsg.has_credentials());
        Q_ASSERT(loginMsg.has_password());

        constexpr users u;

        auto prep = db.prepare(uh::selectCredentials(u.name == parameter(u.name) or
                                                     u.uid == parameter(u.uid) or
                                                     u.email == parameter(u.email) ) );
        auto &param = prep.params;


        const auto &cred = loginMsg.get_credentials();

        if(cred.is_authorized_by_nickname())
            param.name = cred.get_nickname();
        else if( cred.is_authorized_by_email() )
            param.email = cred.get_email();
        else
            param.uid = cred.get_uid();


        auto queryRes = db(prep);

        if ( queryRes.empty() ){
            raise_loginError(res::ILogin::Error_UserDontExists );
        }
        else{
            const auto &row = queryRes.front();

            string salt = row.salt;
            string hash = row.password;
            string hashed_pass = PasswordHash::hashPassword( loginMsg.get_password(), salt );

            if( hashed_pass == hash )
                goToOnlineState(db, row.uid );
            else{
                saveUserActionInDatabase(db, row.uid , "wrong password");
                raise_loginError(res::ILogin::Error_WrongNameOrPass );
            }
        }
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
//        sendServerError(protobuf::Error_AccesDeny);
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

bool UserPU::userExists(DB &db, const string &name, const string &email )
{
    auto query = db.prepare(uh::selectExists(u.name == parameter(u.name) || u.email == parameter(u.email)));

    query.params.name = name;
    query.params.email = email;

    return db(query).front().exists;
}

}
}
