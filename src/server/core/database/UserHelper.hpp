#pragma once

#include "user.pb.h"
#include "idatabase.h"

#include "sql_schema/t_users.h"
#include "sql_schema/t_inventories.h"
#include "sql_schema/t_user_inventories.h"
#include "sql_schema/t_user_history.h"

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

class UserHelper {
public:
    static optional<int64_t> getUserIdByName (DB &db, const string &name);
    static optional<int64_t> getUserIdByEmail(DB &db, const string &email);

    static void insertUser(DB &db, const UserReq_Add &msg);
};

}
}
