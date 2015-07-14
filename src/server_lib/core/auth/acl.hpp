#pragma once

#include <vector>

#include "utils/sqlpp_helper.hpp"
#include "../idatabase.h"

#include "sql_schema/t_acl.h"
#include "sql_schema/t_users.h"
#include "sql_schema/t_action.h"
#include "sql_schema/t_implemented_action.h"
#include "sql_schema/t_privilege.h"


#include "common.pb.h"

using std::vector;
using std::string;
using sqlpp::toBool;
using sqlpp::tableName;

namespace auth {

enum Groups {
    GROUP_root  = 1<<1,
    GROUP_users = 1<<2,
    GROUP_inventories = 1<<3
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
    AccesControl( quint64 uid ):
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

        schema::t_action ac;
        schema::t_privilege pr;
        schema::t_users u;

        ///TODO read group from cache
        quint64 userGroups = 0;


        auto aclInfo = db( sqlpp::select( u.c_group )
                           .from(u)
                           .where( u.c_uid == m_userId ) );
        if(aclInfo.empty())
            return false; // no user
        userGroups = aclInfo.front().c_group;

        auto res = db(sqlpp::select(ac.c_title)
           .from(ac.left_outer_join(pr).on(pr.c_related_table == tablename
                                           and pr.c_action == ac.c_title
                                           and pr.c_type == "table" ))
           .where( ac.c_apply_object == toBool(false)
                   and ( toBool(( userGroups & groupsroot ) != 0)
                        or (pr.c_role == "user" and pr.c_who == m_userId )
                        or (pr.c_role == "group" and (pr.c_who & userGroups) != 0 )
                        )
                   )
           );

        for (const auto& row: res)
            if(row.c_title == action )
                return true;

        return false;
    }

    template<typename TAB>
    bool checkUserAction(const string &action, quint64 objectid){
        DB db;
        return checkUserAction<TAB>(db, action, objectid);
    }

    template<typename TAB>
    bool checkUserAction(DB &db, const string &action, quint64 objectid){
        TAB acl;
        schema::t_action act;
        schema::t_implemented_action ia;
        schema::t_privilege pr;

        if( checkBasicPerms(db,action,objectid) )
            return true;

        auto res = db( sqlpp::select().flags(sqlpp::distinct).columns(act.c_title)
                       .from(act
                             .inner_join(acl).on(acl.c_uid == objectid)
                             .inner_join(ia).on(ia.c_action == act.c_title
                                                and ia.c_table == tableName<TAB>()
                                                and (ia.c_status == 0 or ((ia.c_status & acl.c_status) != 0))
                                                )
                             .left_outer_join(pr).on(pr.c_related_table == tableName<TAB>()
                                                     and pr.c_action == act.c_title
                                                     and (   (  pr.c_type == "object" and pr.c_related_uid == objectid)
                                                          or (  pr.c_type == "global" )
                                                          or ( (pr.c_role == "self")
                                                               and toBool(m_userId  == objectid )
                                                               and toBool(tableName<TAB>() == tableName<schema::t_users>() ))
                                                          )
                                                     )
                             )
                       .where(
                           (act.c_title == action) and
                           act.c_apply_object
                           and ((
                                    (    pr.c_role == "user"        and pr.c_who == m_userId )
                                    or ( pr.c_role == "owner"       and acl.c_owner == m_userId )
                                    or ( pr.c_role == "owner_group" and ((acl.c_group & m_userAcl.group()) != 0))
                                    or ( pr.c_role == "group"       and ((pr.c_who & m_userAcl.group()) != 0))
                                    )
                                or (pr.c_role == "self"))
                           )
                       );

        for (const auto& row: res)
            if(row.c_title == action )
                return true;

        return false;
    }


private:

    bool checkBasicPerms(DB &db, const string &action, quint64 objectid){
        // check if root, and return true if so (root can everything :) )
        if(m_userId == rootId )
            return true;

        Acl objectAcl;

        ///TODO
        /// 1: save the acl info in chace and update it only once a while to prevent db roundtrips
        ///    according to this a simple 'todo' list
        ///     1. give Acl acces to thread cache
        ///     2. check is acl has ben already taken from database and valid
        ///     3. check date od databese query
        ///     4. check acl
        ///     5. save value in cache
        /// 2: Change this to event based operations
        ///     One thread changes object's acl info, and propagate it by the whole serwer (each thread)
        /// 3: Provide a GLOBAL cache, and synchronize writes to that one object in whole system(and take 1)
        ///     but without date chacking

        schema::t_acl acl;
        auto aclInfo = db( sqlpp::select( sqlpp::all_of(acl) )
                           .from(acl)
                           .where( acl.c_uid == m_userId || acl.c_uid == objectid ) );
        if(aclInfo.empty())
            return false; // no object found

        while(!aclInfo.empty()){
            if(aclInfo.front().c_uid == m_userId)
                getAcl(m_userAcl, aclInfo);
            else
                getAcl(objectAcl, aclInfo);
            aclInfo.pop_front();
        }

        if ((m_userAcl.group() & groupsroot) != 0)
            return true;
        if( (action == "read") && (((objectAcl.unixperms() & other_read) != 0) || (((objectAcl.unixperms() & owner_read) != 0) && objectAcl.owner() == m_userId ) || (( (objectAcl.unixperms() & group_read) != 0) && ( (objectAcl.group() & m_userAcl.group()) != 0 )))  ){
            return true;
        }
        if( (action == "write") && (((objectAcl.unixperms() & other_write) != 0) || (((objectAcl.unixperms() & owner_write) != 0) && objectAcl.owner() == m_userId ) || (( (objectAcl.unixperms() & group_write) != 0) && ( (objectAcl.group() & m_userAcl.group()) != 0 )))  ){
            return true;
        }
        if( (action == "delete") && (((objectAcl.unixperms() & other_delete) != 0) || (((objectAcl.unixperms() & owner_delete) != 0) && objectAcl.owner() == m_userId ) || (( (objectAcl.unixperms() & group_delete) != 0) && ( (objectAcl.group() & m_userAcl.group()) != 0 )))  ){
            return true;
        }

        return false;
    }


    template<class Data>
    void getAcl(Acl& acl, const Data &aclInfo){
        acl.set_uid       ( aclInfo.front().c_uid         );
        acl.set_owner     ( aclInfo.front().c_owner       );
        acl.set_unixperms ( aclInfo.front().c_unixperms   );
        acl.set_status    ( aclInfo.front().c_status      );
        acl.set_group     ( aclInfo.front().c_group       );
    }

    quint64 m_userId;
    Acl m_userAcl;
};
}

