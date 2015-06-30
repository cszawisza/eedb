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
using namespace schema;
using namespace pb;

void log_action(DB& db, quint64 uid, const string &action){
    constexpr t_user_history uh;
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
    constexpr t_users u;
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
                u.c_config = userConfig.toStdString() // must be a proper JSON document no need to parametrize
            );

    ///TODO save avatar image
    //        if(det.has_avatar())
    //            ??

    // run query
    auto pre = db.prepare(query);
    pre.params.c_name  = basic.name();
    pre.params.c_email = basic.email();
    if(basic.has_description())
        pre.params.c_description = basic.description();
    if(det.has_address())
        pre.params.c_address = det.address();
    if(det.has_phone_number())
        pre.params.c_phonenumber = det.phone_number();

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

    Q_ASSERT(user().id() > 0);
    Q_ASSERT(user().isOnline() );

    auto uid = user().id();
    DB db;
    constexpr t_users u;
    auto userData = db(sqlpp::select(u.c_name, u.c_email, u.c_config, u.c_owner, u.c_status, u.c_group, u.c_unixperms )
       .from(u)
       .where(u.c_uid == uid ));

//    auto userStorages = db(select(s.c_uid, s.c_owner, s.c_group, s.c_unixperms, s.c_status, s.c_name )
//                           .from(s.inner_join(us)
//                                 .on(us.c_storage_id == s.c_uid) )
//                           .where(us.c_user_id == uid ));

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
        addResp( true, MissingRequiredField);
        error = true;
        return;
    }

    // check required fields
    if( msg.password().length() < 2 ){
        addResp(true, PasswordToShort);
        error = true;
    }
    if( basic.name().length() > 72){
        addResp(true, UserNameToLong);
        error = true;
    }
    if( basic.email().length() > 255 ){
        addResp(true, EmailAddressToLong);
        error = true;
    }
    if(!mailREX.exactMatch(QString::fromStdString(basic.email()))){
        addResp(true, EmailNotValidate);
        error = true;
    }

    // check optional fields
    if( det.has_address() && det.address().length() >= 1000 ){
        addResp(true, AddressToLong);
        error = true;
    }
    if( basic.has_description() && basic.description().length() >= 100000 ){
        addResp(true, DescriptionToLong);
        error = true;
    }
    if( det.has_phone_number() && det.phone_number().length() >= 20 ){
        addResp(true, BadPhoneNumber);
        error = true;
    }

    if (error)
        return;

    DB db;
    if(user().isOnline()){
        auth::AccesControl acl(user().id());

        if(acl.checkUserAction<t_users>("create"))
            addUser(db, msg);
        else{
            ///TODO response: no acces
        }
    }
    else
    {
        if( userExists( basic.name(), basic.email() ) )
            addResp(true, UserAlreadyExists );
        else
            addUser(db, msg);
    }
}

void eedb::handlers::User::handle_login(const MsgUserRequest_Login &loginMsg)
{
    protbuf::ServerResponse res = protbuf::ServerResponse::default_instance();

    auto add_resp = [&]( bool isError, Replay err_code){
        auto code = res.add_codes();
        code->set_error(isError);
        code->set_code(err_code);
        addResponse(res);
    };

    if(user().isOnline()){
        add_resp(true, UserAlreadyLogged );
    }
    else
    {
        DB db;
        quint64 c_uid, number;
        bool exists = false;
        constexpr t_users u;
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
                user().mutable_basic().set_id(c_uid);
                user().goOnline();
                loadUserCache();
            }
            else{
                log_action(db, c_uid, "wrong password");
                add_resp(true, LoginDeny );
            }
        }
    }
}

void eedb::handlers::User::handle_logout(const MsgUserRequest_Logout &logoutMsg)
{
    DB db;
    log_action(db, user().id(), "logout");
}

void eedb::handlers::User::handle_modify(const MsgUserRequest_Modify &msg)
{
}

void eedb::handlers::User::handle_remove(const MsgUserRequest_Remove &msg)
{
    if(!msg.has_cred()){
        ///TODO add response
        //        addResp(true, );
        return;
    }

    ///TODO remove user config
    ///TODO remove user files/items etc
    ///TODO check if user can remove user with cred
    auto cred = msg.cred();
    DB db;
    constexpr t_users u;
    auth::AccesControl acl(user().id());
    auto query = dynamic_remove(db.connection()).from(u).dynamic_where();
    dynamic_cred(query, cred);

    if (acl.checkUserAction<schema::t_users>("delete", msg.cred().id())){
//        remove
    }
    db(query);
}

void eedb::handlers::User::handle_get(const MsgUserRequest_Get &getMsg)
{
    ///TODO check if user is logged
    ///TODO check if can read from users table
}

void eedb::handlers::User::handle_changePasswd(const MsgUserRequest_ChangePasswd &msg)
{
    ///TODO check if is logged in
    ///TODO check if want to reset passwd or to change passwd
    ///TODO change passwd to self or to someone else

    DB db;
    auth::AccesControl acl(user().id());

    if(acl.checkUserAction<schema::t_users>(db,"change_password",msg.uid())){

    }

//    log_action(db, c_uid, "change password");
}

bool eedb::handlers::User::userExists(string name, string email)
{
    ///FIXME change to exists
    /// fix when driver bugfix is avalible
    DB db;
    constexpr t_users u;
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

