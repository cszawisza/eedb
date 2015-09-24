#include "user.h"

#include "sqlpp11/sqlpp11.h"

#include "database/UserHelper.hpp"

#include <iostream>
#include "auth/acl.hpp"
#include "spdlog/spdlog.h"
#include <QRegExp>

using eedb::utils::PasswordHash;
using namespace schema;
using namespace pb;
using sqlpp::postgresql::pg_exception;

namespace eedb{
namespace handlers{


void log_action(DB& db, uint64_t uid, const string &action){
    constexpr t_user_history uh;
    try{
        db(insert_into(uh).set(uh.c_uid = uid, uh.c_action = action ));
    }
    catch(const pg_exception &e){
        ///TODO proper exception handling
        spdlog::get("Server")->error("{}: {}", __PRETTY_FUNCTION__, e.what() );
    }
}

template<typename D, typename C>
boost::optional<uint64_t> getUserId( const D &db, const C &cred){
    constexpr t_users u;
    if( cred.has_name())
        return eedb::db::UserHelper::getUserId(db, u.c_name == cred.name() );
    else if( cred.has_email() )
        return eedb::db::UserHelper::getUserId(db, u.c_email == cred.email() );
    else
        return eedb::db::UserHelper::getUserId(db, u.c_uid == cred.id() );
}

void User::process(pb::ClientRequest &msgReq)
{
    DB db;
    process(db, msgReq);
}

void User::process(DB &db, ClientRequest &msgReq)
{
    m_response.Clear();
    // Check if this is the message that handler wants
    Q_ASSERT( msgReq.data_case() == pb::ClientRequest::kUserReqFieldNumber );
    Q_ASSERT( msgReq.has_userreq() );

    auto req = msgReq.userreq();

    if(user()->isOffline()){
        UserReq::ActionCase msgType = req.action_case();
        if ( msgType == UserReq::kAdd )
            handle_add(db, *req.mutable_add() );
        else if( msgType == UserReq::kLogin)
            handle_login(db, req.login() );
    }
    else{
        UserReq::ActionCase msgType = req.action_case();
        switch ( msgType ) {
        case UserReq::kAdd:
            handle_add(db, *req.mutable_add() );
            break;
        case UserReq::kLogin:
            handle_login(db, req.login() );
            break;
        case UserReq::kLogout:
            handle_logout(db, req.logout() );
            break;
        case UserReq::kGet:
            handle_get(db, req.get() );
            break;
        case UserReq::kRemove:
            handle_remove(db, req.remove() );
            break;
        case UserReq::kModify:
            handle_modify(db, req.modify() );
            break;
        case UserReq::kChangePasswd:
            handle_changePasswd(db, req.changepasswd());
            break;
        case UserReq::ACTION_NOT_SET:
            // send server error
            break;
        }
    }
    addResponseMessage();
}

void User::addUser(DB &db, const UserReq_Add &msg)
{
    try{
        eedb::db::UserHelper::insertUser(db, msg);
        auto uid = db.lastInsertId( sqlpp::tableName<t_acl>(), "c_uid");
        addErrorCode(UserRes_Reply_UserAddOk );
        log_action(db, uid, "register" );
    }
    catch (const pg_exception &e) {
        ///TODO log message
        ///TODO proper exception handling (by class, etc)
        addErrorCode(UserRes_Reply_UserAlreadyExists);
    }
}

void User::addErrorCode(UserRes_Reply err)
{
    m_response.add_code(err);
}

void User::loadUserCache(DB &db, uint64_t uid)
{
    constexpr t_users u;
//    constexpr t_inventories i;
//    constexpr t_user_inventories ui;

    ///TODO move to user helper::getAllUserData
    auto &ud = db(sqlpp::select(
                      u.c_name,
                      u.c_email,
                      u.c_config,

                      u.c_address,
                      u.c_description,
                      u.c_phonenumber,

                      u.c_owner,
                      u.c_status,
                      u.c_group,
                      u.c_unixperms)
       .from(u)
       .where(u.c_uid == uid )).front();

    auto basic = user()->mutable_basic();
    auto acl   = user()->mutable_acl();

    basic->set_id   ( uid );
    basic->set_name ( ud.c_name );
    basic->set_email( ud.c_email );
    basic->set_description( ud.c_description );

    acl->set_uid(uid);
    acl->set_group(ud.c_group);
    acl->set_status( ud.c_status );
    acl->set_unixperms( ud.c_unixperms );

    ///TODO get config

//    auto userInventories = db(select(s.c_uid, s.c_owner, s.c_group, s.c_unixperms, s.c_status, s.c_name )
//                           .from(s.inner_join(us)
//                                 .on(us.c_storage_id == s.c_uid) )
//                           .where(us.c_user_id == uid ));

}

void User::addResponseMessage()
{
    add_response()->mutable_userres()->CopyFrom(m_response);
}

void User::handle_add(DB &db, UserReq_Add &msg)
{
    QRegExp mailREX("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
    bool error = false;

    mailREX.setCaseSensitivity(Qt::CaseInsensitive);
    mailREX.setPatternSyntax(QRegExp::RegExp);
    const auto &basic = msg.basic();
    const auto &det = msg.details();

    if(!basic.has_name() || !basic.has_email() || !msg.has_password()){
        addErrorCode( UserRes_Reply_MissingRequiredField);
        error = true;
        return;
    }

    // check required fields
    if( msg.password().length() < 2 ){
        addErrorCode(UserRes_Reply_PasswordToShort);
        error = true;
    }
    if( basic.name().length() > 72){
        addErrorCode(UserRes_Reply_UserNameToLong);
        error = true;
    }
    if( basic.email().length() > 255 ){
        addErrorCode(UserRes_Reply_EmailAddressToLong);
        error = true;
    }
    if(!mailREX.exactMatch(QString::fromStdString(basic.email()))){
        addErrorCode(UserRes_Reply_EmailNotValidate);
        error = true;
    }

    // check optional fields
    if( det.has_address() && det.address().length() >= 1000 ){
        addErrorCode(UserRes_Reply_AddressToLong);
        error = true;
    }
    if( basic.has_description() && basic.description().length() >= 100000 ){
        addErrorCode(UserRes_Reply_DescriptionToLong);
        error = true;
    }
    if( det.has_phone_number() && det.phone_number().length() >= 20 ){
        addErrorCode(UserRes_Reply_BadPhoneNumber);
        error = true;
    }

    if (error)
        return;

    if(user()->isOnline()){
        auth::AccesControl acl(user()->id());

        if(acl.checkUserAction<t_users>("create"))
            addUser(db, msg);
        else{
            sendAccesDeny();
        }
    }
    else{
        if( userExists( db, basic.name(), basic.email() ) )
            addErrorCode(UserRes_Reply_UserAlreadyExists );
        else
        {
            if(msg.has_acl())
                msg.clear_acl(); // force default values

            addUser(db, msg);
        }
    }
}

void User::goToOnlineState(DB &db, uint64_t uid)
{
    log_action(db, uid, "login");
    addErrorCode(UserRes_Reply_LoginPass);

    user()->goOnline();

    loadUserCache(db, uid);
}

void User::handle_login(DB &db, const UserReq_Login &loginMsg)
{
    if(user()->isOnline()){
        addErrorCode(UserRes_Reply_UserOnline );
    }
    else
    {
        constexpr t_users u;
        auto c_uid = getUserId(db, loginMsg.cred());
        if (!c_uid){
            addErrorCode(UserRes_Reply_UserDontExist );
        }
        else{
            auto cred = db(select(u.c_password, u.c_salt).from(u).where(u.c_uid == c_uid.get()));

            string salt = cred.front().c_salt;
            string hash = cred.front().c_password;
            string hashed_pass = PasswordHash::hashPassword( loginMsg.password(), salt );

            if( hashed_pass == hash )
                goToOnlineState(db, c_uid.get() );
            else{
                log_action(db, c_uid.get() , "wrong password");
                addErrorCode(UserRes_Reply_LoginDeny );
            }
        }
    }
}

void User::handle_logout(DB &db, const UserReq_Logout &logoutMsg)
{
    log_action(db, user()->id(), "logout");
    user()->goOffLine();
}

void User::handle_modify(DB &db, const UserReq_Modify &msg)
{
    ///TODO implement
}

template<typename T, typename C>
void dynamix_exists( T &query, const C &cred){
    constexpr t_users u;
    if( cred.has_name())
        query.where.add( u.c_name == cred.name() );
    else if( cred.has_email() )
        query.where.add( u.c_email == cred.email() );
    else
        query.where.add( u.c_uid == cred.id() );
}

void User::handle_remove( DB &db, const UserReq_Remove &msg)
{
    if(!msg.has_cred()){
        addErrorCode(UserRes_Reply_MissingRequiredField);
        return;
    }

    ///TODO remove user files/items/history etc
    ///TODO check if user can remove user with cred
    auto cred = msg.cred();
    constexpr t_users u;
    auth::AccesControl acl(user()->id());

    if (acl.checkUserAction<schema::t_users>("delete", msg.cred().id())){
        auto query = dynamic_remove(db.connection()).from(u).dynamic_where();
        dynamix_exists(query, cred);
        db(query);
    }
    else
        sendAccesDeny();
}

void User::handle_get(DB &db, const UserReq_Get &getMsg)
{
    ///TODO check if can read from users table/user
}

void User::handle_changePasswd(DB &db, const UserReq_ChangePasswd &msg)
{
    auth::AccesControl acl(user()->id());

    if(msg.has_resetpasswd() && msg.resetpasswd() ){
        ///TODO reset passwd
    }

    else{
        if(acl.checkUserAction<schema::t_users>("change_password",msg.uid())){
            ///TODO check if old pass is same as new
            ///TODO set new passwd
//            DB db;
//            PasswordHash passwd;
//            passwd.setPassword( msg.new_() );
//            db(update)
        }
        else
            sendAccesDeny();
    }
}

bool User::userExists(DB &db, string name, string email)
{
    constexpr t_users u;
    auto q = sqlpp::select(exists(sqlpp::select( u.c_uid )
            .from(u)
            .where(u.c_name == parameter(u.c_name) || u.c_email == parameter(u.c_email) )
            ));
    auto query = db.prepare(q);
    query.params.c_name = name;
    query.params.c_email = email;
    auto result = db(query);

    return result.front().exists;
}

}
}
