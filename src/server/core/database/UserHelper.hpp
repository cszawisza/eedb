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

using namespace pb;
using eedb::utils::PasswordHash;

namespace eedb{
namespace db{

class T_User {
public:
    static int64_t getUserIdByName(DB &db, const string &name);
    static void insertUser(DB &db, const MsgUserRequest_Add msg);
};

}
}
