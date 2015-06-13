#ifndef ACL_H
#define ACL_H

#include <vector>
#include <string>

#include <QtCore>

#include "idatabase.h"

#include "sqlpp11/sqlpp11.h"
#include "sql_schema/t_acl.h"
#include "sql_schema/t_action.h"
#include "sql_schema/t_implemented_action.h"
#include "sql_schema/t_privilege.h"
#include "sql_schema/t_users.h"

using std::vector;
using std::string;

class Acl : public DatabasePool
{
public:
    Acl();
    ~Acl();

    template<class Acl>
    vector<string> getUserPermissions(Acl acl, quint64 userid, quint64 objectid)
    {
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
        int usergroups = 0;
        vector<string> result;
        DatabaseConnectionProvider db (this);

        schema::t_users user;
        schema::t_action act;
        schema::t_implemented_action ia;
        schema::t_privilege pr;

        for( auto const &row : db( select(user.c_group)
                                   .from(user)
                                   .where( user.c_uid == userid ) )) {
            usergroups = row.c_group;
        }

        string tablename = "t_users";

        auto res = db( sqlpp::select().flags(sqlpp::distinct).columns(act.c_title)
                       .from(act
                             .inner_join(acl).on(acl.c_uid == objectid)
                             .inner_join(ia).on(ia.c_action == act.c_title and ia.c_table == tablename and (ia.c_status == 0 or ((ia.c_status & acl.c_status) != 0)) )
                             .left_outer_join(pr).on(pr.c_related_table == tablename and pr.c_action == act.c_title and ((pr.c_type == "object" and pr.c_related_uid == objectid) or (pr.c_type == "global") or ( (pr.c_role == "self") and sqlpp::verbatim<sqlpp::boolean>((userid == objectid) ? "TRUE " : "FALSE ") and sqlpp::verbatim<sqlpp::boolean>( (tablename == "users") ? "TRUE " : "FALSE "))))
                             )
                       .where(
                           act.c_apply_object
                           and ((
                                    (    act.c_title == "read"   and (( (acl.c_unixperms & other_read)   != 0 ) or (( (acl.c_unixperms & owner_read)   != 0)  and acl.c_owner == userid ) or (( (acl.c_unixperms & group_read)   != 0) and ( (acl.c_group & usergroups) != 0 ))) )
                                    or ( act.c_title == "write"  and (( (acl.c_unixperms & other_write)  != 0 ) or (( (acl.c_unixperms & owner_write)  != 0)  and acl.c_owner == userid ) or (( (acl.c_unixperms & group_write)  != 0) and ( (acl.c_group & usergroups) != 0 ))) )
                                    or ( act.c_title == "delete" and (( (acl.c_unixperms & other_delete) != 0 ) or (( (acl.c_unixperms & owner_delete) != 0)  and acl.c_owner == userid ) or (( (acl.c_unixperms & group_delete) != 0) and ( (acl.c_group & usergroups) != 0 ))) )
                                    or ( pr.c_role == "user"        and pr.c_who == userid )
                                    or ( pr.c_role == "owner"       and acl.c_owner == userid )
                                    or ( pr.c_role == "owner_group" and ((acl.c_group & usergroups) != 0))
                                    or ( pr.c_role == "group"       and ((pr.c_who & usergroups) != 0))
                                    or ( sqlpp::verbatim<sqlpp::boolean>(((usergroups & groupsroot) != 0) ? "TRUE " : "FALSE " )) )
                                or (pr.c_role == "self"))
                           )
                       );

        for (const auto& row: res)
            result.push_back(row.c_title);

        return result;
    }
};

#endif // ACL_H
