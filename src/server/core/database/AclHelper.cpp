#include "AclHelper.hpp"

#include "sql_schema/stat.h"

namespace eedb{
namespace db {


optional<protobuf::Acl> AclHelper::getAcl(DB &db, UID objectID)
{
    return eedb::db::AclHelper::getAcl<schema::stat>(db, objectID);
}

void AclHelper::updateAcl(DB &db, protobuf::Acl objectID ) throw(sqlpp::postgresql::pg_exception){

}

}
}
