#include "UserHelper.hpp"

#include <Interfaces/UserRequests.hpp>
#include <Interfaces/AclData.hpp>

namespace eedb{
namespace db{

UID UserHelper::insertUser(DB &db, const requests::user::IAdd &msg)
{
    constexpr schema::users u;

    //    const auto basic = msg.basic();
    //    const auto det = msg.details();
    //    const auto &conf= msg.config();
    utils::PasswordHash passwd;
    passwd.setPassword( msg.get_password() );

    //    utils::UserConfig userConfig( conf );

    // run query
    auto pre = db.prepare(sqlpp::postgresql::insert_into(u)
                          .set(
                              u.stat_group = parameter(u.stat_group),
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
                              //u.config = userConfig.toStdString(), // must be a proper JSON document no need to parametrize
                              u.avatar = parameter(u.avatar)
            ).returning(u.uid));

    pre.params.name  = msg.get_nickname();
    pre.params.email = msg.get_email();

    if(msg.has_avatar()){
        QByteArray ba = QByteArray::fromRawData(msg.get_avatar().data(), msg.get_avatar().size() );
        pre.params.avatar = ba.toBase64().toStdString();
    }

//    if( msg.has_acl() ){
//        const auto &stat = msg.get_acl();
//        pre.params.stat_group = stat.has_groups() ? stat.get_groups() : auth::GROUP_users | auth::GROUP_inventories;
//        pre.params.unixperms = stat.has_unixperms() ? stat.get_unixperms().toInteger() : UnixPermissions({6,4,4}).toInteger();
//        pre.params.owner = stat.has_owner() ? stat.get_owner() : 1;
//        pre.params.status = stat.has_status() ? stat.get_status() : (int)auth::State_Normal;
//    }
//    else{
        pre.params.stat_group = auth::GROUP_users | auth::GROUP_inventories;
        pre.params.unixperms = UnixPermissions({6,4,4}).toInteger();
        pre.params.owner = 1;
        pre.params.status = (int)auth::State_Normal;
//    }

    if(msg.has_description())
        pre.params.description = msg.get_description();

    if(msg.has_address())
        pre.params.address = msg.get_address();

    if(msg.has_phoneNumber())
        pre.params.phonenumber = msg.get_phoneNumber();

    auto insertedId = db(pre);

    return insertedId.front().uid;
}
}
}
