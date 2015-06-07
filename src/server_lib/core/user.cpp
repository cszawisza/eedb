#include "user.h"

#include "sqlpp11/sqlpp11.h"

#include "sql_schema/users.h"
#include "sql_schema/t_acl.h"
#include "sql_schema/t_action.h"

#include "pb_cpp/user.pb.h"

#include <QCryptographicHash>
#include <QDateTime>

void eedb::parsers::User::process()
{
    // Check if this is the message that handler wants
    Q_ASSERT( getRequest().data_case() == protbuf::ClientRequest::kMsgUserReqFieldNumber );
    Q_ASSERT( getRequest().has_msguserreq() );

    auto req = getRequest().msguserreq();

    using user::MsgUserRequest;
    MsgUserRequest::DataCase msgType = req.data_case();
    switch ( msgType ) {
    case MsgUserRequest::kAdd:
        parse_add( req.add() );
        break;
    case MsgUserRequest::kLogin:
        parse_login( req.login() );
        break;
    case MsgUserRequest::kLogout:
        parse_logout( req.logout() );
        break;
    case MsgUserRequest::kGet:
        parse_get( req.get() );
        break;
    case MsgUserRequest::kRemove:
        parse_remove( req.remove() );
        break;
    case MsgUserRequest::kModify:
        parse_modify( req.modify() );
        break;
    case MsgUserRequest::DATA_NOT_SET:
        // send server error
        break;
    }
}

void eedb::parsers::User::parse_add(const user::MsgUserRequest_Add &msg)
{
    DatabaseConnectionProvider db(this);

    ///TODO validate email address
    ///TODO validate rest of fields (lengths)

//    if( verify)

    if(cache()->userStatus().isLogged()){
        ///TODO check if user can add another user
    }
    else
    {
        schema::users u;
        const auto &det = msg.details();
        const auto &conf= msg.config();

        bool e = db(select(count(u.c_uid))
                    .from(u)
                    .where(u.name == det.name() || u.email == det.email() )
                    ).front().count > 0;

        if( e ){
            protbuf::ServerResponse res;
            auto code = res.add_codes();
            code->set_error(true);
            code->set_code( user::Replay::UserAlreadyExists);

            addResponse(res);
        }
        else{
            ///TODO salt password
            auto timestamp = QDateTime::currentMSecsSinceEpoch();
            auto salt = QCryptographicHash::hash( QByteArray(QString::number( timestamp ).toLatin1() ),
                                                  QCryptographicHash::Sha3_512).toHex();
            auto password = QByteArray::fromRawData(msg.password().data(), msg.password().length() ).toHex();
            QByteArray hash = QCryptographicHash::hash(salt + password, QCryptographicHash::Sha3_512);

            auto query = dynamic_insert_into(db.connection(), u)
                    .dynamic_set(
                        u.name = parameter(u.name),
                        u.email = parameter(u.email),
                        u.password = hash.toHex().toStdString(),
                        u.salt = salt.toStdString(),
                        u.address = parameter(u.address),
                        u.phonenumber = parameter(u.phonenumber),
                        u.description = parameter(u.description)
                    );

            ///TODO save avatar image
            //        if(det.has_avatar())
            //            ??

            ///TODO save config
            /// create a class that will handle all configuration options an return it as string
            //        if(msg.has_config()){
            //            conf.
            //        }

            // run query
            auto pre = db.prepare(query);
            pre.params.name  = det.name();
            pre.params.email = det.email();

            if(det.has_address())
                pre.params.address = det.address();
            if(det.has_phone_number())
                pre.params.phonenumber = det.phone_number();
            if(det.has_description())
                pre.params.description = det.description();

            try{
                db(pre);
            }
            catch (sqlpp::exception e) {
                qDebug() << QString::fromStdString(e.what());
            }

        }
    }
}

void eedb::parsers::User::parse_login(const user::MsgUserRequest_Login &loginMsg)
{
    DatabaseConnectionProvider db(this);

}

void eedb::parsers::User::parse_logout(const user::MsgUserRequest_Logout &logoutMsg)
{

}

void eedb::parsers::User::parse_modify(const user::MsgUserRequest_Modify &modifyMsg)
{

}

void eedb::parsers::User::parse_remove(const user::MsgUserRequest_Remove &delateMsg)
{

}

void eedb::parsers::User::parse_get(const user::MsgUserRequest_Get &getMsg)
{

}

