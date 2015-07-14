#pragma once

#include "core/idatabase.h"

#include "implementedaction.hpp"
#include "action.hpp"

#include "sql_schema/t_privilege.h"
#include "utils/sqlpp_helper.hpp"
#include <string>

using sqlpp::tableName;

namespace auth{

// user, a group, or in the case of an “object” privilege, the object’s owner or owner_group. A further special case, in my system, is “self.”';
enum RoleID {
    Role_User,
    Role_Group,
    Role_Object,
    Role_Owner,
    Role_OwnerGroup,
    Role_Self
};

struct Role{
    static std::string name(RoleID id);
    static RoleID id(const std::string &name);
private:

};

enum TypeID{
    Type_Object,
    Type_Table,
    Type_Global
};

struct Type {
    static std::string name(TypeID id);
    static TypeID id(const std::string &name);
};

class Privilege{
public:
    Privilege():
        m_action(""),m_oid(0),m_related_table(""),
        m_role(Role_User), m_status(Status_Normal),
        m_type(Type_Object),m_who(0)
    {}

    void setType(TypeID id){
        m_type = id;
    }

    void setRole(RoleID id){
        m_role = id;
    }

    void setRole(const std::string &role){
        m_role = Role::id(role);
    }

    void setImplementedAction( const ImplementedAction &action ){
        m_action = action.title();
        m_status = action.status();
        m_related_table = action.tableName();
    }

    void setWho(quint64 uid){
        m_who = uid;
    }

    void setObjectID(quint64 oid){
        m_oid = oid;
    }

    bool force_save(DB &db){
        static constexpr schema::t_privilege pr;

        auto action = Action(m_action, m_type == Type_Object ? Object : Table );
        auto iaction= ImplementedAction(m_action,m_status,m_related_table);

        if(!action.actionExists(db) ){
            action.save(db);
        }
        if(!iaction.exists(db) ){
            iaction.save(db);
        }

        try{
            db(insert_into(pr)
               .set(pr.c_role = Role::name(m_role),
                    pr.c_who = m_who,
                    pr.c_action = m_action,
                    pr.c_type = Type::name(m_type),
                    pr.c_related_table = m_related_table,
                    pr.c_related_uid = m_oid ));
        }
        catch(sqlpp::exception e){
            std::cout << e.what();
        }


        return true;
    }
    bool exists(DB &db){
        static constexpr schema::t_privilege pr;

        if(m_role == Role_User ){
            return db(sqlpp::select
                      (sqlpp::exists(sqlpp::select(sqlpp::all_of(pr))
                              .from(pr)
                              .where(pr.c_role == Role::name(m_role) and
                                     pr.c_who == m_who and
                                     pr.c_type == Type::name(Type_Object) and
                                     pr.c_related_table == m_related_table )
                              )
                       )
                      ).front().exists;
        }

        return true;
    }

private:
    string m_action;
    TypeID m_type;
    string m_related_table;
    Status m_status;
    RoleID m_role;
    quint64 m_who = 0;
    quint64 m_oid = 0;
};

}
