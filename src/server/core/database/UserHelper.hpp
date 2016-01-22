#pragma once

#include "idatabase.h"

#include "config.h"
#include "sql_schema/users.h"
#include "sql_schema/user_history.h"

#include <boost/optional.hpp>

namespace requests{
namespace user{
class IAdd;
}
}

namespace eedb{
namespace db{

class UserHelper {
public:
    static UID getRootId(DB &db);

    template< typename T >
    static auto selectId( T&& t ){
        constexpr schema::users u;
        return sqlpp::select(u.uid)
                .from(u)
                .where( std::forward<T>(t) )
                .limit(1);
    }

    template< typename T >
    static auto selectExists( T&& t ){
        constexpr schema::users u;
        return sqlpp::select
                  (sqlpp::exists
                   (sqlpp::select(u.uid)
                    .from(u)
                    .where( std::forward<T>(t) )
                    .limit(1))
                   );
    }

    template< typename T >
    static auto selectCredentials( T&& t ){
        constexpr schema::users u;
        return sqlpp::select(u.uid, u.password, u.salt)
                .from(u)
                .where( std::forward<T>(t) )
                .limit(1);
    }

    template< typename T >
    static auto selectAll( T&& t ){
        constexpr schema::users u;
        return sqlpp::select( sqlpp::all_of(u) )
                .from(u)
                .where( std::forward<T>(t) )
                .limit(1);
    }

    static UID insertUser(DB &db, const requests::user::IAdd &msg);
    static boost::optional<UID> m_rootID;
};

}
}
