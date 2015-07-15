#include "privilege.hpp"
#include "utils/CTcrc32.hpp"
#include "spdlog/spdlog.h"
using std::string;
namespace auth {

struct PrivilegeRow{
    PrivilegeRow():
        role(""), who(0), action(""),
        type(""), related_table(""), related_uid(0)
    {
    }

    string  role;
    quint64 who;
    string  action;
    string  type;
    string  related_table;
    quint64 related_uid;
};

std::string Role::name(RoleID id) {
    switch (id) {
    case Role_User:
        return "user";
        break;
    case Role_Group:
        return "group";
        break;
    case Role_Object:
        return "object";
        break;
    case Role_Owner:
        return "owner";
        break;
    case Role_OwnerGroup:
        return "owner_group";
        break;
    case Role_Self:
        return "self";
        break;
    default:
        break;
    }
}

RoleID Role::id(const string &name)
{
    auto hash = RT_CRC32( name.c_str() );
    switch (hash) {
    case CT_CRC32("user"):
        return Role_User;
        break;
    case CT_CRC32("group"):
        return Role_Group;
        break;
    case CT_CRC32("object"):
        return Role_Object;
        break;
    case CT_CRC32("owner"):
        return Role_Owner;
        break;
    case CT_CRC32("owner_group"):
        return Role_OwnerGroup;
        break;
    case CT_CRC32("self"):
        return Role_Self;
        break;
    default:
        /// throw an exception or what?
        break;
    }

    return Role_User;
}

std::string auth::Type::name(auth::TypeID id)
{
    switch (id) {
    case Type_Object:
        return "object";
        break;
    case Type_Table:
        return "table";
        break;
    case Type_Global:
        return "global";
        break;
    default:
        break;
    }
    return "object";
}

TypeID Type::id(const std::string &name)
{
    auto hash = RT_CRC32( name.c_str() );
    switch (hash) {
    case CT_CRC32("object"):
        return Type_Object;
        break;
    case CT_CRC32("table"):
        return Type_Table;
        break;
    case CT_CRC32("global"):
        return Type_Global;
        break;
    default:
        /// throw an exception or what?
        break;
    }

    return Type_Object;
}

bool Privilege::force_save(DB &db) const{
    auto action = Action(m_action, m_type == Type_Object ? Object : Table );
    auto iaction= ImplementedAction(m_action,m_status,m_related_table);

    if(!action.exists(db) ){
        action.save(db);
    }
    if(!iaction.exists(db) ){
        iaction.save(db);
    }

    PrivilegeRow row;
    row.role = Role::name(m_role);
    row.who = (m_role == Role_Group ? m_groupid : m_who);
    row.action = m_action;
    row.type = Type::name(m_type);
    row.related_table = m_related_table;
    row.related_uid = m_oid;

    saveInDb(db, row);

    return true;
}

bool Privilege::exists(DB &db) const{
    static constexpr schema::t_privilege pr;

    if(m_role == Role_User ){
        return db(sqlpp::select
                  (sqlpp::exists(sqlpp::select(sqlpp::all_of(pr))
                                 .from(pr)
                                 .where(pr.c_role == Role::name(m_role) and
                                        pr.c_who == (m_role == Role_Group ? m_groupid : m_who) and
                                        pr.c_type == Type::name(Type_Object) and
                                        pr.c_related_table == m_related_table )
                                 )
                   )
                  ).front().exists;
    }


    return true;
}

bool Privilege::saveInDb(DB &db, const PrivilegeRow &row) const {
    static constexpr schema::t_privilege pr;

    try{
        db(insert_into(pr)
           .set(pr.c_role = row.role,
                pr.c_who = row.who,
                pr.c_action = row.action,
                pr.c_type = row.type,
                pr.c_related_table = row.related_table,
                pr.c_related_uid = row.related_uid ));
    }
    catch(sqlpp::exception e){
        spdlog::get("Server")->error("{}: {}", __PRETTY_FUNCTION__, e.what() );
    }
}

}
