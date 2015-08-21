#include "AclHelper.hpp"

#include "sql_schema/t_acl.h"

namespace eedb{
namespace db {

Acl AclHelper::getAcl(DB &db, uint64_t objectID)
{
    static constexpr schema::t_acl a;
    Acl acl = Acl::default_instance();
    auto row = db(sqlpp::select(sqlpp::all_of(a)).from(a).where(a.c_uid == objectID ));

    if( !row.empty() ){
        acl.set_group( row.front().c_group );
        acl.set_owner( row.front().c_owner );
        acl.set_status( row.front().c_status );
        acl.set_uid( row.front().c_uid );
        acl.set_unixperms( row.front().c_unixperms );
    }

    return acl;
}

}
}