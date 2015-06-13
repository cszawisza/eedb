#include "user.h"

#include "sqlpp11/sqlpp11.h"

#include "sql_schema/t_users.h"

#include "utils/userconfig.h"
#include "utils/hash_passwd.h"

#include "acl.h"

using eedb::utils::PasswordHash;

schema::t_users u;

template<typename T, typename C>
void dynamic_cred( T &query, const C &cred){
    if( cred.has_name())
        query.where.add( u.c_name == cred.name() );
    else if( cred.has_email() )
        query.where.add( u.c_email == cred.email() );
    else
        query.where.add( u.c_uid == cred.id() );
}



void eedb::handlers::User::process()
{
    // Check if this is the message that handler wants
    Q_ASSERT( getRequest().data_case() == protbuf::ClientRequest::kMsgUserReqFieldNumber );
    Q_ASSERT( getRequest().has_msguserreq() );

    auto req = getRequest().msguserreq();

    using user::MsgUserRequest;
    MsgUserRequest::DataCase msgType = req.data_case();
    switch ( msgType ) {
    case MsgUserRequest::kAdd:
        handle_add( req.add() );
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
    case MsgUserRequest::DATA_NOT_SET:
        // send server error
        break;
    }
}

void eedb::handlers::User::handle_add(const user::MsgUserRequest_Add &msg)
{
    DatabaseConnectionProvider db(this);
    ///TODO validate email address
    ///TODO validate rest of fields (lengths)
    Acl acl;
    auto can_add = acl.getUserPermissions(u,1,1);
    if(cache()->userStatus().isLogged()){
        ///TODO check if user can add another user
    }
    else
    {
        protbuf::ServerResponse res = protbuf::ServerResponse::default_instance();

        auto add_resp = [&]( bool isError, Replay err_code){
            auto code = res.add_codes();
            code->set_error(isError);
            code->set_code(err_code);
            addResponse(res);
        };

        const auto &det = msg.details();
        const auto &conf= msg.config();

        if( db(select(count(u.c_uid) )
              .from(u)
              .where(u.c_name == det.name() || u.c_email == det.email() )
//              .group_by( u.c_uid )
              ).front().count > 0)
        {
            add_resp(true, UserAlreadyExists );
        }
        else{
            ///TODO move password/salt hash generation to database
            /// using http://www.postgresql.org/docs/9.4/static/pgcrypto.html
            PasswordHash passwd;
            passwd.setPassword( msg.password() );

            eedb::utils::UserConfig userConfig( conf );
            auto query = dynamic_insert_into(db.connection(), u)
                    .dynamic_set(
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
                add_resp(false, UserAddOk);
            }
            catch (sqlpp::exception) {
                ///TODO print error
                add_resp(true, UserAlreadyExists);
            }
            catch ( ... ){
                qDebug() << "Unknown error";
            }

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

    if(cache()->userStatus().isLogged()){
        add_resp(true, UserAlreadyLogged );
    }
    else
    {
        DatabaseConnectionProvider db(this);

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
        number = queryResult.front().count;
        c_uid = queryResult.front().c_uid;

        Q_ASSERT(number <= 1);
        exists = number == 1;

            ///TODO load user config to cache
            auto cred = db(select(u.c_password, u.c_salt).from(u).where(u.c_uid == c_uid));

            string salt = cred.front().c_salt;
            string hash = cred.front().c_password;
            string hashed_pass = PasswordHash::hashPassword( loginMsg.password(), salt );

            if( hashed_pass == hash ){
                add_resp(false, LoginPass);
            }else{
                add_resp(true, LoginDeny );
                cache()->userStatus().setStatus(UserStatus::logged);
            }
        }
    }
}

void eedb::handlers::User::handle_logout(const user::MsgUserRequest_Logout &logoutMsg)
{
    DatabaseConnectionProvider db(this);
}

void eedb::handlers::User::handle_modify(const user::MsgUserRequest_Modify &modifyMsg)
{
    DatabaseConnectionProvider db(this);
}

void eedb::handlers::User::handle_remove(const user::MsgUserRequest_Remove &delateMsg)
{
    ///TODO remove user config
    ///TODO remove user files/items etc
    ///TODO check if user can remove user with cred
    DatabaseConnectionProvider db(this);
    auto cred = delateMsg.cred();

    auto query = dynamic_remove(db.connection()).from(u).dynamic_where();
    dynamic_cred(query, cred);

    Acl acl;
    acl.getUserPermissions(u, 32, 32);
    db(query);
}

void eedb::handlers::User::handle_get(const user::MsgUserRequest_Get &getMsg)
{
    DatabaseConnectionProvider db(this);
}

