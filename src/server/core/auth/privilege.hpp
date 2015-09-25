#pragma once

#include "database/idatabase.h"

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

struct PrivilegeRow;

class GroupPriviliges{

};

class Privilege{
public:
    Privilege():
        m_action(""),m_oid(0),m_related_table(""),
        m_role(Role_User), m_status(State_Normal),
        m_type(Type_Object),m_who(0)
    {}

    Privilege &giveUser( uint64_t uid ){
        setRole(Role_User);
        setGroup(0);
        setWho(uid);
        return *this;
    }

    Privilege &giveGroup(uint64_t gid){
        setRole(Role_Group);
        setGroup(gid);
        setWho(0);
        return *this;
    }

    Privilege &privilegeFor( const string &action ){
        setImplementedAction(ImplementedAction(action));
        return *this;
    }

    Privilege &inState( ObjectState state ){
        m_status  = state;
        return *this;
    }

    template<typename T>
    Privilege &forTable(const T&){
        m_type = Type_Table;
        setObjectID(0);
        m_related_table = sqlpp::tableName<T>();
        return *this;
    }

    Privilege &onObject( uint64_t object ){
        m_type = Type_Object;
        setObjectID(object);
        return *this;
    }

    template<typename T>
    Privilege &inTable(const T&){
        m_related_table = sqlpp::tableName<T>();
        return *this;
    }

    bool force_save(DB &db) const ;
    bool exists(DB &db) const ;
private:

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

    void setWho(uint64_t uid){
        m_who = uid;
    }

    void setGroup(uint64_t gid){
        m_groupid = gid;
    }

    void setObjectID(uint64_t oid){
        m_oid = oid;
    }

    bool saveInDb(DB &db, const PrivilegeRow &row) const;

    string m_action;
    uint64_t m_oid = 0;
    string m_related_table;
    RoleID m_role;
    ObjectState m_status;
    TypeID m_type;
    uint64_t m_who = 0;
    uint64_t m_groupid = 0;
};

}
