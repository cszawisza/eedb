#include "AclHelper.hpp"

#include "sql_schema/t_acl.h"

namespace eedb{
namespace db {


optional<pb::Acl> AclHelper::getAcl(DB &db, UID objectID)
{
    return eedb::db::AclHelper::getAcl<schema::t_acl>(db, objectID);
}

void AclHelper::updateAcl(DB &db, pb::Acl objectID ) throw(sqlpp::postgresql::pg_exception){

}

}
}
