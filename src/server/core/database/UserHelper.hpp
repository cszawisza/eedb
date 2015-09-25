#pragma once

#include "user.pb.h"
#include "idatabase.h"

#include "sql_schema/t_users.h"
#include "sql_schema/t_user_inventories.h"
#include "sql_schema/t_user_history.h"

#include "sql_schema/t_inventories.h"

#include "utils/hash_passwd.h"
#include "utils/userconfig.h"
#include "utils/unixPerms.hpp"

#include "auth/implementedaction.hpp"
#include "auth/privilege.hpp"
#include "auth/acl.hpp"


using namespace pb;
using eedb::utils::PasswordHash;


namespace eedb{
namespace db{

struct UserData {
    UserData():
        uid(0){}

    uint64_t uid;
    string name;
};

class UserHelper {
public:
    template< typename T >
    static auto selectId( T&& t ){
        constexpr schema::t_users u;
        return sqlpp::select(u.c_uid)
                .from(u)
                .where( std::forward<T>(t) )
                .limit(1);
    }

    template< typename T >
    static auto selectExists( T&& t ){
        constexpr schema::t_users u;
        return sqlpp::select
                  (sqlpp::exists
                   (sqlpp::select(u.c_uid)
                    .from(u)
                    .where( std::forward<T>(t) )
                    .limit(1))
                   );
    }

    template< typename T >
    static auto selectCredentials( T&& t ){
        constexpr schema::t_users u;
        return sqlpp::select(u.c_uid, u.c_password, u.c_salt)
                .from(u)
                .where( std::forward<T>(t) )
                .limit(1);
    }

    template< typename T >
    static auto selectAll( T&& t ){
        constexpr schema::t_users u;
        return sqlpp::select(
                    u.c_uid,
                    u.c_name,
                    u.c_email,
                    u.c_config,

                    u.c_address,
                    u.c_description,
                    u.c_phonenumber,

                    u.c_owner,
                    u.c_status,
                    u.c_group,
                    u.c_unixperms )
                .from(u)
                .where( std::forward<T>(t) )
                .limit(1);
    }

    static void insertUser(DB &db, const UserReq_Add &msg);
};

}
}
