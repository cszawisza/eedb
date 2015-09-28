#pragma once

#include "config.h"
#include "idatabase.h"
#include "common.pb.h"

#include "sql_schema/t_acl.h"

#include <boost/optional.hpp>

using boost::optional;

namespace eedb{
namespace db{

class AclHelper {
public:
    template < typename T , typename W>
    static auto selectAclFrom ( W&& where){
        constexpr T u;
        return sqlpp::select(
                    u.c_uid,
                    u.c_owner,
                    u.c_unixperms,
                    u.c_group,
                    u.c_status)
                .from(u)
                .where( std::forward<W>(where) )
                .limit(1);
    }

    template < typename W>
    static auto selectAcl( W&& where){
        return selectAclFrom<schema::t_acl>( std::forward<W>(where) );
    }

    template < typename T , typename W >
    static auto updateWhere (const pb::Acl &data, W &&where ){
        constexpr T tab;
        auto du = dynamic_update(DB::connection(), tab).dynamic_set().dynamic_where();
        du.where.add( std::forward<W>(where) );

        if( data.has_group() )
            du.assignments.add( tab.c_group = data.group() );
        if( data.has_owner() )
            du.assignments.add( tab.c_owner = data.owner() );
        if( data.has_status() )
            du.assignments.add( tab.c_status = data.status() );
        if( data.has_unixperms() )
            du.assignments.add( tab.c_unixperms = data.unixperms() );

        return du;
    }

    static auto update (const pb::Acl &data ){
        constexpr schema::t_acl a;
        auto uid = data.has_uid()?data.uid() : 0;
        return updateWhere<schema::t_acl>(data, a.c_uid == uid );
    }

//    template< typename T >
//    static auto update(const pb::Acl &data){
//        return
//    }

    template<typename T>
    static optional<pb::Acl> getAcl(DB &db, UID objectID)
    {
        static constexpr T a;
        boost::optional<pb::Acl> optionalAclData;
        auto row = db( selectAclFrom<decltype(a)>( a.c_uid == objectID ));

        if( !row.empty() ){
            pb::Acl acl = pb::Acl::default_instance();
            acl.set_group( row.front().c_group );
            acl.set_owner( row.front().c_owner );
            acl.set_status( row.front().c_status );
            acl.set_uid( row.front().c_uid );
            acl.set_unixperms( row.front().c_unixperms );
            optionalAclData = acl;
        }

        return optionalAclData;
    }

    static optional<pb::Acl> getAcl(DB &db, UID objectID);
    static void updateAcl(DB &db, pb::Acl objectID ) throw(sqlpp::postgresql::pg_exception);
};
}
}

