#pragma once

#include "config.h"
#include "idatabase.h"
#include "common.pb.h"

#include "sql_schema/stat.h"

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
                    u.uid,
                    u.owner,
                    u.unixperms,
                    u.stat_group,
                    u.status)
                .from(u)
                .where( std::forward<W>(where) );
    }

    template < typename W>
    static auto selectAcl( W&& where){
        return selectAclFrom<schema::stat>( std::forward<W>(where) );
    }

    template < typename T , typename W >
    static auto updateWhere (const protobuf::Acl &data, W &&where ){
        constexpr T tab;
        auto du = dynamic_update(DB::connection(), tab).dynamic_set().dynamic_where();
        du.where.add( std::forward<W>(where) );

        if( data.has_group() )
            du.assignments.add( tab.stat_group = data.group() );
        if( data.has_owner() )
            du.assignments.add( tab.owner = data.owner() );
        if( data.has_status() )
            du.assignments.add( tab.status = data.status() );
        if( data.has_unixperms() )
            du.assignments.add( tab.unixperms = data.unixperms() );

        return du;
    }

    static auto update (const protobuf::Acl &data ){
        constexpr schema::stat a;
        auto uid = data.has_uid()?data.uid() : 0;
        return updateWhere<schema::stat>(data, a.uid == uid );
    }

//    template< typename T >
//    static auto update(const protobuf::Acl &data){
//        return
//    }

    template<typename T>
    static optional<protobuf::Acl> getAcl(DB &db, UID objectID)
    {
        static constexpr T a;
        boost::optional<protobuf::Acl> optionalAclData;
        auto row = db( selectAclFrom<decltype(a)>( a.uid == objectID ));

        if( !row.empty() ){
            protobuf::Acl stat = protobuf::Acl::default_instance();
            stat.set_group( row.front().stat_group );
            stat.set_owner( row.front().owner );
            stat.set_status( row.front().status );
            stat.set_uid( row.front().uid );
            stat.set_unixperms( row.front().unixperms );
            optionalAclData = stat;
        }

        return optionalAclData;
    }

    static optional<protobuf::Acl> getAcl(DB &db, UID objectID);
    static void updateAcl(DB &db, protobuf::Acl objectID ) throw(sqlpp::postgresql::pg_exception);
};
}
}

