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

    template< typename D, typename... T >
    static optional<UserData> getAllUserDataWhere(D db, T&&... t){
        constexpr schema::t_users u;
//        constexpr schema::t_user_history uh;
//        constexpr schema::t_user_inventories ui;

        optional<UserData> ud;

        auto data = db( sqlpp::select( sqlpp::all_of(u) )
                        .from(u)
                        .where( std::forward<T>(t)... )
                        .limit(1) );

        if(!data.empty()){
            ud = UserData();
            const auto &front = data.front();
            ud->uid = front.c_uid;
            ud->name = front.c_name;
        }

        return ud;
    }

//    template< typename P, typename V, typename T >
//    static void fillParam( P &p, const V &v ){
//        p.params.
//    }

    template< typename D, typename... T >
    static optional<uint64_t> getUserId(D db, T&&... t){
        constexpr schema::t_users u;
        const int args = sizeof...(T);

//        auto prep = db.prepare(sqlpp::select(u.c_uid).from(u).where( u.c_email == parameter(u.c_email) ));
//        prep.params.c_email = email;

        auto res = db(sqlpp::select(u.c_uid)
                      .from(u)
                      .where( std::forward<T>(t)... )
                      .limit(1));

        optional<uint64_t> id;
        if(!res.empty())
            id = res.front().c_uid;
        return id;
    }

    template< typename D, typename... T >
    static bool exists(D db, T&&... t){
        constexpr schema::t_users u;
        return db(sqlpp::select(sqlpp::exists(sqlpp::select(u.c_uid)
                                              .from(u)
                                              .where(std::forward<T>(t)...)
                                              .limit(1))))
                .front().exists;
    }

    static void insertUser(DB &db, const UserReq_Add &msg);
};

}
}
