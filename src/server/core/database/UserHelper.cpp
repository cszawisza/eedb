#include "UserHelper.hpp"

namespace eedb{
namespace db{

UID UserHelper::insertUser(DB &db, const UserReq_Add &msg)
{
    constexpr schema::users u;
    const auto &acl = msg.acl();
    const auto &basic = msg.basic();
    const auto &det = msg.details();
    const auto &conf= msg.config();
    PasswordHash passwd;
    passwd.setPassword( msg.password() );

    utils::UserConfig userConfig( conf );

    // run query
    auto pre = db.prepare(sqlpp::postgresql::insert_into(u)
                          .set(
                              u.acl_group = parameter(u.acl_group),
                              u.unixperms = parameter(u.unixperms),
                              u.owner = parameter(u.owner),
                              u.status = parameter(u.status),
                              u.name = parameter(u.name),
                              u.email = parameter(u.email),
                              u.password = passwd.hash(),
                              u.salt = passwd.salt(),
                              u.address = parameter(u.address),
                              u.phonenumber = parameter(u.phonenumber),
                              u.description = parameter(u.description),
                              u.config = userConfig.toStdString(), // must be a proper JSON document no need to parametrize
                              u.avatar = parameter(u.avatar)
            ).returning(u.uid));

    pre.params.name  = basic.name();
    pre.params.email = basic.email();

    if(basic.has_avatar()){
        QByteArray ba = QByteArray::fromRawData(basic.avatar().data(), basic.avatar().size() );
        pre.params.avatar = ba.toBase64().toStdString();
    }

    if( msg.has_acl() ){
        pre.params.acl_group = acl.has_group() ? acl.group() : auth::GROUP_users | auth::GROUP_inventories;
        pre.params.unixperms = acl.has_unixperms() ? acl.unixperms() : UnixPermissions({6,4,4}).toInteger();
        pre.params.owner = acl.has_owner() ? acl.owner() : 1;
        pre.params.status = acl.has_status() ? acl.status() : (int)auth::State_Normal;
    }
    else{
        pre.params.acl_group = auth::GROUP_users | auth::GROUP_inventories;
        pre.params.unixperms = UnixPermissions({6,4,4}).toInteger();
        pre.params.owner = 1;
        pre.params.status = (int)auth::State_Normal;
    }


    if(basic.has_description())
        pre.params.description = basic.description();

    if(det.has_address())
        pre.params.address = det.address();

    if(det.has_phone_number())
        pre.params.phonenumber = det.phone_number();

    auto insertedId = db(pre);

    return insertedId.front().uid;
}
}
}
