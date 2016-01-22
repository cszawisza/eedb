#pragma once

#include <vector>

#include "utils/sqlpp_helper.hpp"
#include "database/AclHelper.hpp"
#include "database/idatabase.h"

#include "sql_schema/stat.h"
#include "sql_schema/users.h"
#include "sql_schema/action.h"
#include "sql_schema/implemented_action.h"
#include "sql_schema/privilege.h"

#include "common.pb.h"

using std::vector;
using std::string;
using sqlpp::toBool;
using sqlpp::tableName;

namespace auth {

enum Groups {
    GROUP_root  = 1<<0,
    GROUP_users = 1<<1,
    GROUP_inventories = 1<<2,
    GROUP_categories = 1<<3,
    GROUP_items = 1<<4
};


constexpr int owner_read    = 1<<8;
constexpr int owner_write   = 1<<7;
constexpr int owner_delete  = 1<<6;
constexpr int group_read    = 1<<5;
constexpr int group_write   = 1<<4;
constexpr int group_delete  = 1<<3;
constexpr int other_read    = 1<<2;
constexpr int other_write   = 1<<1;
constexpr int other_delete  = 1<<0;

constexpr int groupsroot = 1;
constexpr int rootId = 1;

using std::string;

class AccesControl {
public:
    AccesControl( uint64_t uid ):
        m_userId(uid)
    {
    }

    template<typename TAB>
    bool checkUserAction(const string &action){
        DB db;
        return checkUserAction<TAB>(db, action);
    }

    template<typename TAB>
    bool checkUserAction(DB &db, const string &action){
        const auto &tablename = sqlpp::name_of<TAB>::char_ptr();

        schema::action ac;
        schema::privilege pr;
        schema::users u;

        ///TODO read group from cache
        uint64_t userGroups = 0;


        auto statInfo = db( sqlpp::select( u.stat_group )
                           .from(u)
                           .where( u.uid == m_userId ) );
        if(statInfo.empty())
            return false; // no user
        userGroups = statInfo.front().stat_group;

        auto res = db(sqlpp::select(ac.title)
           .from(ac.left_outer_join(pr).on(pr.related_table_name == tablename
                                           and pr.action == ac.title
                                           and pr.type == "table" ))
           .where( ac.apply_object == toBool(false)
                   and ( toBool(( userGroups & groupsroot ) != 0)
                        or (pr.role == "user" and pr.who == m_userId )
                        or (pr.role == "group" and (pr.who & userGroups) != 0 )
                        )
                   )
           );

        for (const auto& row: res){
            if(row.title == action )
                return true;
        }

        return false;
    }

    template<typename TAB>
    bool checkUserAction(const string &action, uint64_t objectid){
        DB db;
        return checkUserAction<TAB>(db, action, objectid);
    }

    template<typename TAB>
    bool checkUserAction(DB &db, const string &action, uint64_t objectid){
        TAB stat;
        schema::action act;
        schema::implemented_action ia;
        schema::privilege pr;

        if( checkBasicPerms(db,action,objectid) )
            return true;

        auto res = db( sqlpp::select().flags(sqlpp::distinct).columns(act.title)
                       .from(act
                             .inner_join(stat).on(stat.uid == objectid)
                             .inner_join(ia).on(ia.action == act.title
                                                and ia.table_name == tableName<TAB>()
                                                and (ia.status == 0 or ((ia.status & stat.status) != 0))
                                                )
                             .left_outer_join(pr).on(pr.related_table_name == tableName<TAB>()
                                                     and pr.action == act.title
                                                     and (   (  pr.type == "object" and pr.related_object_uid == objectid)
                                                          or (  pr.type == "global" )
                                                          or ( (pr.role == "self")
                                                               and toBool(m_userId  == objectid )
                                                               and toBool(tableName<TAB>() == tableName<schema::users>() ))
                                                          )
                                                     )
                             )
                       .where(
                           (act.title == action) and
                           act.apply_object
                           and ((
                                    (    pr.role == "user"        and pr.who == m_userId )
                                    or ( pr.role == "owner"       and stat.owner == m_userId )
                                    or ( pr.role == "owner_group" and ((stat.stat_group & m_userAcl.group()) != 0))
                                    or ( pr.role == "group"       and ((pr.who & m_userAcl.group()) != 0))
                                    )
                                or (pr.role == "self"))
                           )
                       );

        for (const auto& row: res)
            if(row.title == action )
                return true;
        return false;
    }


private:

    bool checkBasicPerms(DB &db, const string &action, uint64_t objectid);


    template<class Data>
    void readAclFromData(protobuf::Acl& stat, const Data &statInfo){
        stat.set_uid       ( statInfo.front().uid         );
        stat.set_owner     ( statInfo.front().owner       );
        stat.set_unixperms ( statInfo.front().unixperms   );
        stat.set_status    ( statInfo.front().status      );
        stat.set_group     ( statInfo.front().stat_group       );
    }

    int64_t m_userId;
    protobuf::Acl m_userAcl;
};
}

