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

#include <boost/optional.hpp>

using namespace pb;
using eedb::utils::PasswordHash;
using boost::optional;

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


    static optional<int64_t> getUserIdByName (DB &db, const string &name);
    static optional<int64_t> getUserIdByEmail(DB &db, const string &email);

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

    template< typename D, typename T >
    static optional<UserData> getAllUserDataWhere(D db, T&& t){
        constexpr schema::t_users u;

        optional<UserData> ud;

        auto data = db( sqlpp::select( sqlpp::all_of(u) )
                        .from(u)
                        .where( std::forward<T>(t) )
                        .limit(1) );

        if(!data.empty()){
            ud = UserData();
            const auto &front = data.front();
            ud->uid = front.c_uid;
            ud->name = front.c_name;
        }

        return ud;
    }

    template< typename D, typename T >
    static optional<uint64_t> getUserIdWhere(D db, T&& t){
        constexpr schema::t_users u;
        auto res = db(sqlpp::select(u.c_uid)
                      .from(u)
                      .where( std::forward<T>(t) )
                      .limit(1));

        optional<uint64_t> id;
        if(!res.empty())
            id = res.front().c_uid;
        return id;
    }

    static void insertUser(DB &db, const UserReq_Add &msg);
};

}
}
