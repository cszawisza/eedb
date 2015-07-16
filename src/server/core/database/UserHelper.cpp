#include "UserHelper.hpp"

namespace eedb{
namespace db{

int64_t T_User::getUserIdByName(DB &db, const string &name){
    constexpr schema::t_users u;
    auto prep = db.prepare(sqlpp::select(u.c_uid).from(u).where( u.c_name == parameter(u.c_name) ));
    prep.params.c_name = name;
    auto res = db(prep);

    if(res.empty())
        return 0;
    return res.front().c_uid;
}

void T_User::insertUser(DB &db, const MsgUserRequest_Add msg)
{
    constexpr schema::t_users u;
    const auto &acl = msg.acl();
    const auto &basic = msg.basic();
    const auto &det = msg.details();
    const auto &conf= msg.config();
    PasswordHash passwd;
    passwd.setPassword( msg.password() );

    utils::UserConfig userConfig( conf );
    auto query = insert_into(u)
            .set(
                u.c_group = parameter(u.c_group),
                u.c_unixperms = parameter(u.c_unixperms),
                u.c_owner = parameter(u.c_owner),
                u.c_status = parameter(u.c_status),
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

    if( msg.has_acl() ){
        pre.params.c_group = acl.has_group() ? acl.group() : auth::GROUP_users || auth::GROUP_inventories;
        pre.params.c_unixperms = acl.has_unixperms() ? acl.unixperms() : UnixPermissions({6,4,4}).toInteger();
        pre.params.c_owner = acl.has_owner() ? acl.owner() : 1;
        pre.params.c_status = acl.has_status() ? acl.status() : (int)auth::State_Normal;
    }
    else{
        pre.params.c_group = auth::GROUP_users || auth::GROUP_inventories;
        pre.params.c_unixperms = UnixPermissions({6,4,4}).toInteger();
        pre.params.c_owner = 1;
        pre.params.c_status = (int)auth::State_Normal;
    }


    if(basic.has_description())
        pre.params.c_description = basic.description();

    if(det.has_address())
        pre.params.c_address = det.address();

    if(det.has_phone_number())
        pre.params.c_phonenumber = det.phone_number();

    db(pre);
}
}
}
