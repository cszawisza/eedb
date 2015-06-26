#include "user.h"

#include "sqlpp11/sqlpp11.h"

#include "sql_schema/t_users.h"
#include "sql_schema/t_inventories.h"
#include "sql_schema/t_user_inventories.h"
#include "sql_schema/t_user_history.h"

#include "utils/userconfig.h"
#include "utils/hash_passwd.h"
#include <iostream>
#include "acl.h"
#include <QRegExp>

using eedb::utils::PasswordHash;

schema::t_users u;
schema::t_user_inventories us;
schema::t_inventories s;
schema::t_user_history uh;

void log_action(DB& db, quint64 uid, const string &action){
    try{
        db(insert_into(uh).set(uh.c_uid = uid, uh.c_action = action ));
    }
    catch(sqlpp::exception e){
        ///TODO log
        std::cout << e.what();
    }
}

template<typename T, typename C>
void dynamic_cred( T &query, const C &cred){
    if( cred.has_name())
        query.where.add( u.c_name == cred.name() );
    else if( cred.has_email() )
        query.where.add( u.c_email == cred.email() );
    else
        query.where.add( u.c_uid == cred.id() );
}



void eedb::handlers::User::process(protbuf::ClientRequest &msgReq)
{
    // Check if this is the message that handler wants
    Q_ASSERT( msgReq.data_case() == protbuf::ClientRequest::kMsgUserReqFieldNumber );
    Q_ASSERT( msgReq.has_msguserreq() );

//    db.takeFromPool();
    auto req = msgReq.msguserreq();

    using user::MsgUserRequest;
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

//    db.pushToPool();
}

void eedb::handlers::User::addUser(const user::MsgUserRequest_Add &msg)
{
    const auto &det = msg.details();
    const auto &conf= msg.config();
    PasswordHash passwd;
    passwd.setPassword( msg.password() );
    DB db;

    eedb::utils::UserConfig userConfig( conf );
    auto query = insert_into(u)
            .set(
                u.c_group = msg.acl().group(),
                u.c_unixperms = msg.acl().unixperms(),
                u.c_owner = msg.acl().owner(),
                u.c_status = msg.acl().status(),
                u.c_name = parameter(u.c_name),
                u.c_email = parameter(u.c_email),
                u.c_password = passwd.hash(),
                u.c_salt = passwd.salt(),
                u.c_address = parameter(u.c_address),
                u.c_phonenumber = parameter(u.c_phonenumber),
                u.c_description = parameter(u.c_description),
                u.c_config = userConfig.toStdString() // must be a proper JSON document no need to parametrize
            );

    ///TODO save avatar image
    //        if(det.has_avatar())
    //            ??

    // run query
    auto pre = db.prepare(query);
    pre.params.c_name  = det.name();
    pre.params.c_email = det.email();
    if(det.has_address())
        pre.params.c_address = det.address();
    if(det.has_phone_number())
        pre.params.c_phonenumber = det.phone_number();
    if(det.has_description())
        pre.params.c_description = det.description();

    try{
        db(pre);
        addResp(false, UserAddOk);
    }
    catch (sqlpp::exception) {
        addResp(true, UserAlreadyExists);
    }
    catch ( ... ){
        qDebug() << "Unknown error";
    }
}

void eedb::handlers::User::addResp( bool isError, Replay err_code){
    protbuf::ServerResponse res = protbuf::ServerResponse::default_instance();
    auto code = res.add_codes();
    code->set_error(isError);
    code->set_code(err_code);
    addResponse(res);
}

void eedb::handlers::User::loadUserCache()
{
    ///TODO load user config to cache

    ///TODO get acl?

    Q_ASSERT(cache()->user().data().id > 0);
    Q_ASSERT(cache()->user().isLogged() );

    auto uid = cache()->user().data().id;
    DB db;
    auto userData = db(select(u.c_name, u.c_email, u.c_config, u.c_owner, u.c_status, u.c_group, u.c_unixperms )
       .from(u)
       .where(u.c_uid == uid ));

//    auto userStorages = db(select(s.c_uid, s.c_owner, s.c_group, s.c_unixperms, s.c_status, s.c_name )
//                           .from(s.inner_join(us)
//                                 .on(us.c_storage_id == s.c_uid) )
//                           .where(us.c_user_id == uid ));

}

void eedb::handlers::User::handle_add(user::MsgUserRequest_Add &msg)
{
    ///TODO create table that handles login actions taken by user
    ///TODO save information about login in database
    QRegExp mailREX("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
    bool error = false;

    mailREX.setCaseSensitivity(Qt::CaseInsensitive);
    mailREX.setPatternSyntax(QRegExp::RegExp);

    if(!msg.details().has_name() ||msg.details().has_email() || msg.has_password()){
        addResp( true , EmailNotValidate); ///TODO set proper error
        error = true;
    }

    ///TODO validate rest of fields (lengths)
    if( msg.details().name().length() > 72){
        addResp(true, UserNameToLong);
        error = true;
    }

    if(!mailREX.exactMatch(QString::fromStdString(msg.details().email()))){
        addResp(true, EmailNotValidate);
        error = true;
    }

    if( msg.details().email().length() > 255){
        addResp(true, EmailAddressToLong);
        error = true;
    }

    if( msg.password().size() < 2 ){
        addResp(true, PasswordToShort);
        error = true;
    }

    if (error)
        return;

    if(cache()->user().isLogged()){
        auth::AccesControl acl(cache()->user().data().id);
        schema::t_users u;
        if(acl.checkUserAction("create",u))
            addUser(msg);
        else{
            // no acces :(
        }
    }
    else
    {
        if( userExists( msg.details().name(), msg.details().email() ) )
            addResp(true, UserAlreadyExists );
        else{
            msg.mutable_acl()->set_unixperms( 484 ); // rwdr--r--
            msg.mutable_acl()->set_owner( 1 ); ///TODO set owner to self?
            msg.mutable_acl()->set_status( 0 );
            msg.mutable_acl()->set_group( 2 ); ///TODO provide user groups
            addUser(msg);
        }
    }
}

void eedb::handlers::User::handle_login(const user::MsgUserRequest_Login &loginMsg)
{
    protbuf::ServerResponse res = protbuf::ServerResponse::default_instance();

    auto add_resp = [&]( bool isError, Replay err_code){
        auto code = res.add_codes();
        code->set_error(isError);
        code->set_code(err_code);
        addResponse(res);
    };

    if(cache()->user().isLogged()){
        add_resp(true, UserAlreadyLogged );
    }
    else
    {
        DB db;
        quint64 c_uid, number;
        bool exists = false;
        auto s = dynamic_select(db.connection(), count(u.c_uid), u.c_uid )
                .from(u)
                .dynamic_where()
                .dynamic_group_by(u.c_uid);

        dynamic_cred(s,loginMsg.cred());

        auto queryResult = db(s);

        if (queryResult.empty()){
            add_resp(true, UserDontExist );
        }
        else{
            c_uid = queryResult.front().c_uid;

            auto cred = db(select(u.c_password, u.c_salt).from(u).where(u.c_uid == c_uid));

            string salt = cred.front().c_salt;
            string hash = cred.front().c_password;
            string hashed_pass = PasswordHash::hashPassword( loginMsg.password(), salt );

            if( hashed_pass == hash ){
                log_action(db, c_uid, "login");
                add_resp(false, LoginPass);
                cache()->user().data().id = c_uid;
                cache()->user().setIsLogged();
                loadUserCache();
            }
            else{
                log_action(db, c_uid, "wrong password");
                ///TODO auth try in database
                add_resp(true, LoginDeny );
            }
        }
    }
}

void eedb::handlers::User::handle_logout(const user::MsgUserRequest_Logout &logoutMsg)
{
    DB db;
    log_action(db, cache()->user().data().id, "logout");
}

void eedb::handlers::User::handle_modify(const user::MsgUserRequest_Modify &modifyMsg)
{
}

void eedb::handlers::User::handle_remove(const user::MsgUserRequest_Remove &delateMsg)
{
    ///TODO remove user config
    ///TODO remove user files/items etc
    ///TODO check if user can remove user with cred
    auto cred = delateMsg.cred();
    DB db;
    auto query = dynamic_remove(db.connection()).from(u).dynamic_where();
    dynamic_cred(query, cred);

//    getUserPermissions(u, 32);
    db(query);
}

void eedb::handlers::User::handle_get(const user::MsgUserRequest_Get &getMsg)
{
    ///TODO
}

void eedb::handlers::User::handle_changePasswd(const user::MsgUserRequest_ChangePasswd &changePasswd)
{
    ///TODO
//    DB db;
//    log_action(db, c_uid, "change password");
}

bool eedb::handlers::User::userExists(string name, string email)
{
    ///FIXME change to exists
    /// fix when driver bugfix is avalible
    DB db;
    auto q = select( count(u.c_uid) )
                 .from(u)
                 .where(u.c_name == parameter(u.c_name) || u.c_email == parameter(u.c_email) )
                 .group_by( u.c_uid ).limit(1);
    auto query = db.prepare(q);
    query.params.c_name = name;
    query.params.c_email = email;
    auto result = db(query);
    if(result.empty())
        return false;
    return result.front().count > 0;
}

