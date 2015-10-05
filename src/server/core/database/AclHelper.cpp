#include "AclHelper.hpp"

#include "sql_schema/stat.h"

namespace eedb{
namespace db {


optional<pb::Acl> AclHelper::getAcl(DB &db, UID objectID)
{
    return eedb::db::AclHelper::getAcl<schema::stat>(db, objectID);
}

void AclHelper::updateAcl(DB &db, pb::Acl objectID ) throw(sqlpp::postgresql::pg_exception){

}

}
}
