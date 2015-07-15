#include "user.h"

#include "sqlpp11/sqlpp11.h"

#include "sql_schema/t_users.h"
#include "sql_schema/t_inventories.h"
#include "sql_schema/t_user_inventories.h"
#include "sql_schema/t_user_history.h"

#include "utils/userconfig.h"
#include "utils/hash_passwd.h"
#include <iostream>
#include "auth/acl.hpp"
#include "spdlog/spdlog.h"
#include <QRegExp>

using eedb::utils::PasswordHash;
using namespace schema;
using namespace pb;

void log_action(DB& db, quint64 uid, const string &action){
    constexpr t_user_history uh;
    try{
        db(insert_into(uh).set(uh.c_uid = uid, uh.c_action = action ));
    }
    catch(sqlpp::exception e){
        spdlog::get("Server")->error("{}: {}", __PRETTY_FUNCTION__, e.what() );
    }
}

template<typename T, typename C>
void dynamic_cred( T &query, const C &cred){
    constexpr t_users u;
    if( cred.has_name())
        query.where.add( u.c_name == cred.name() );
    else if( cred.has_email() )
        query.where.add( u.c_email == cred.email() );
    else
        query.where.add( u.c_uid == cred.id() );
}

void eedb::handlers::User::process(pb::ClientRequest &msgReq)
{
    m_response.Clear();
    // Check if this is the message that handler wants
    Q_ASSERT( msgReq.data_case() == pb::ClientRequest::kMsgUserReqFieldNumber );
    Q_ASSERT( msgReq.has_msguserreq() );

    auto req = msgReq.msguserreq();

    if(user()->isOffline()){
        MsgUserRequest::ActionCase msgType = req.action_case();
        if ( msgType == MsgUserRequest::kAdd )
            handle_add( *req.mutable_add() );
        else if( msgType == MsgUserRequest::kLogin)
            handle_login( req.login() );
    }
    else{
        MsgUserRequest::ActionCase msgType = req.action_case();
        switch ( msgType ) {
        case MsgUserRequest::kAdd:
            handle_add( *req.mutable_add() );
            break;
        case MsgUserRequest::kLogin:
            handle_login( req.login() );
            break;
        case MsgUserRequest::kLogout:
            handle_logout( req.logout() );
            break;
        case MsgUserRequest::kGet:
            handle_get( req.get() );
            break;
        case MsgUserRequest::kRemove:
            handle_remove( req.remove() );
            break;
        case MsgUserRequest::kModify:
            handle_modify( req.modify() );
            break;
        case MsgUserRequest::kChangePasswd:
            handle_changePasswd( req.changepasswd());
            break;
        case MsgUserRequest::ACTION_NOT_SET:
            // send server error
            break;
        }
    }
    addResponseMessage();
}

void eedb::handlers::User::addUser(DB &db, const MsgUserRequest_Add &msg)
{
    constexpr schema::t_users u;
    const auto &basic = msg.basic();
    const auto &det = msg.details();
    const auto &conf= msg.config();
    PasswordHash passwd;
    passwd.setPassword( msg.password() );

    eedb::utils::UserConfig userConfig( conf );
    auto query = insert_into(u)
            .set(
                u.c_group = msg.acl().has_group() ? msg.acl().group() : auth::GROUP_users | auth::GROUP_inventories, // default to user group
                u.c_unixperms = msg.acl().has_unixperms() ? msg.acl().unixperms() : 484,
                u.c_owner = msg.acl().has_owner() ? msg.acl().owner() : 1,
                u.c_status = msg.acl().has_status() ? msg.acl().status() : 0 ,
                u.c_name = parameter(u.c_name),
                u.c_email = parameter(u.c_email),
                u.c_password = passwd.hash(),
                u.c_salt = passwd.salt(),
                u.c_address = parameter(u.c_address),
                u.c_phonenumber = parameter(u.c_phonenumber),
                u.c_description = parameter(u.c_description),
                u.c_config = userConfig.toStdString(), // must be a proper JSON document no need to parametrize
                u.c_avatar = parameter(u.c_avatar)
            );

    // run query
    auto pre = db.prepare(query);
    pre.params.c_name  = basic.name();
    pre.params.c_email = basic.email();

    if(basic.has_avatar()){
        QByteArray ba = QByteArray::fromRawData(basic.avatar().data(), basic.avatar().size() );
        pre.params.c_avatar = ba.toBase64().toStdString();
    }

    if(basic.has_description())
        pre.params.c_description = basic.description();
    if(det.has_address())
        pre.params.c_address = det.address();
    if(det.has_phone_number())
        pre.params.c_phonenumber = det.phone_number();

    try{
        db(pre);
        auto uid = db(select(u.c_uid).from(u).where(u.c_name == basic.name())).front().c_uid;
        addErrorCode(false, UserAddOk);
        log_action(db, uid, "register" );
    }
    catch (sqlpp::exception) {
        addErrorCode(true, UserAlreadyExists);
    }
}

void eedb::handlers::User::insertUser(DB &db, const MsgUserRequest_Add msg)
{
    constexpr schema::t_users u;
    const auto &basic = msg.basic();
    const auto &det = msg.details();
    const auto &conf= msg.config();
    PasswordHash passwd;
    passwd.setPassword( msg.password() );

    eedb::utils::UserConfig userConfig( conf );
    auto query = insert_into(u)
            .set(
                u.c_group = msg.acl().has_group() ? msg.acl().group() : 2, // default to user group
                u.c_unixperms = msg.acl().has_unixperms() ? msg.acl().unixperms() : 484,
                u.c_owner = msg.acl().has_owner() ? msg.acl().owner() : 1,
                u.c_status = msg.acl().has_status() ? msg.acl().status() : 0 ,
                u.c_name = parameter(u.c_name),
                u.c_email = parameter(u.c_email),
                u.c_password = passwd.hash(),
                u.c_salt = passwd.salt(),
                u.c_address = parameter(u.c_address),
                u.c_phonenumber = parameter(u.c_phonenumber),
                u.c_description = parameter(u.c_description),
                u.c_config = userConfig.toStdString(), // must be a proper JSON document no need to parametrize
                u.c_avatar = parameter(u.c_avatar)
            );

    // run query
    auto pre = db.prepare(query);
    pre.params.c_name  = basic.name();
    pre.params.c_email = basic.email();

    if(basic.has_avatar()){
        QByteArray ba = QByteArray::fromRawData(basic.avatar().data(), basic.avatar().size() );
        pre.params.c_avatar = ba.toBase64().toStdString();
    }

    if(basic.has_description())
        pre.params.c_description = basic.description();
    if(det.has_address())
        pre.params.c_address = det.address();
    if(det.has_phone_number())
        pre.params.c_phonenumber = det.phone_number();
    db(pre);
}

void eedb::handlers::User::addErrorCode(bool isError, Replay err)
{
    auto code = m_response.add_code();
    code->set_error(isError);
    code->set_code(static_cast<int>(err));
}

void eedb::handlers::User::loadUserCache(DB &db, quint64 uid)
{
    constexpr t_users u;
//    constexpr t_inventories i;
//    constexpr t_user_inventories ui;

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

void eedb::handlers::User::addResponseMessage()
{
    pb::ServerResponse res = pb::ServerResponse::default_instance();
    res.mutable_msguserres()->CopyFrom(m_response);
    addResponse(res);
}

void eedb::handlers::User::handle_add(MsgUserRequest_Add &msg)
{
    QRegExp mailREX("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
    bool error = false;

    mailREX.setCaseSensitivity(Qt::CaseInsensitive);
    mailREX.setPatternSyntax(QRegExp::RegExp);
    const auto &basic = msg.basic();
    const auto &det = msg.details();

    if(!basic.has_name() || !basic.has_email() || !msg.has_password()){
        addErrorCode( true, MissingRequiredField);
        error = true;
        return;
    }

    // check required fields
    if( msg.password().length() < 2 ){
        addErrorCode(true, PasswordToShort);
        error = true;
    }
    if( basic.name().length() > 72){
        addErrorCode(true, UserNameToLong);
        error = true;
    }
    if( basic.email().length() > 255 ){
        addErrorCode(true, EmailAddressToLong);
        error = true;
    }
    if(!mailREX.exactMatch(QString::fromStdString(basic.email()))){
        addErrorCode(true, EmailNotValidate);
        error = true;
    }

    // check optional fields
    if( det.has_address() && det.address().length() >= 1000 ){
        addErrorCode(true, AddressToLong);
        error = true;
    }
    if( basic.has_description() && basic.description().length() >= 100000 ){
        addErrorCode(true, DescriptionToLong);
        error = true;
    }
    if( det.has_phone_number() && det.phone_number().length() >= 20 ){
        addErrorCode(true, BadPhoneNumber);
        error = true;
    }

    if (error)
        return;

    DB db;
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
            addErrorCode(true, UserAlreadyExists );
        else
        {
            if(msg.has_acl())
                msg.clear_acl(); // force default values

            addUser(db, msg);
        }
    }
}

void eedb::handlers::User::goToOnlineState(DB &db, quint64 uid)
{
    log_action(db, uid, "login");
    addErrorCode(false, LoginPass);

    user()->goOnline();

    loadUserCache(db, uid);
}

void eedb::handlers::User::handle_login(const MsgUserRequest_Login &loginMsg)
{
    if(user()->isOnline()){
        addErrorCode(true, UserOnline );
    }
    else
    {
        DB db;
        quint64 c_uid;
        constexpr t_users u;
        auto s = dynamic_select(db.connection(), count(u.c_uid), u.c_uid )
                .from(u)
                .dynamic_where()
                .dynamic_group_by(u.c_uid);

        dynamic_cred(s,loginMsg.cred());

        auto queryResult = db(s);

        if (queryResult.empty()){
            addErrorCode(true, UserDontExist );
        }
        else{
            c_uid = queryResult.front().c_uid;

            auto cred = db(select(u.c_password, u.c_salt).from(u).where(u.c_uid == c_uid));

            string salt = cred.front().c_salt;
            string hash = cred.front().c_password;
            string hashed_pass = PasswordHash::hashPassword( loginMsg.password(), salt );

            if( hashed_pass == hash )
                goToOnlineState(db, c_uid);
            else{
                log_action(db, c_uid, "wrong password");
                addErrorCode(true, LoginDeny );
            }
        }
    }
}

void eedb::handlers::User::handle_logout(const MsgUserRequest_Logout &logoutMsg)
{
    DB db;
    log_action(db, user()->id(), "logout");
    user()->goOffLine();
}

void eedb::handlers::User::handle_modify(const MsgUserRequest_Modify &msg)
{
}

void eedb::handlers::User::handle_remove(const MsgUserRequest_Remove &msg)
{
    if(!msg.has_cred()){
        addErrorCode(true, MissingRequiredField);
        return;
    }

    ///TODO remove user files/items/history etc
    ///TODO check if user can remove user with cred
    auto cred = msg.cred();
    DB db;
    constexpr t_users u;
    auth::AccesControl acl(user()->id());

    if (acl.checkUserAction<schema::t_users>("delete", msg.cred().id())){
        auto query = dynamic_remove(db.connection()).from(u).dynamic_where();
        dynamic_cred(query, cred);
        db(query);
    }
    else
        sendAccesDeny();
}

void eedb::handlers::User::handle_get(const MsgUserRequest_Get &getMsg)
{
    ///TODO check if can read from users table/user
}

void eedb::handlers::User::handle_changePasswd(const MsgUserRequest_ChangePasswd &msg)
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

bool eedb::handlers::User::userExists(DB &db, string name, string email)
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

