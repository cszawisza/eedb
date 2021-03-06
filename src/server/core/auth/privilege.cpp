#include "privilege.hpp"
#include "utils/CTcrc32.hpp"
#include "utils/LogUtils.hpp"

using std::string;
using sqlpp::postgresql::pg_exception;
namespace auth {

struct PrivilegeRow{
    PrivilegeRow():
        role(""), who(0), action(""),
        type(""), related_table(""), related_uid(0)
    {
    }

    string  role;
    uint64_t who;
    string  action;
    string  type;
    string  related_table;
    uint64_t related_uid;
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
    return "";
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
    static constexpr schema::privilege pr;

    if(m_role == Role_User ){
        return db(sqlpp::select
                  (sqlpp::exists(sqlpp::select(sqlpp::all_of(pr))
                                 .from(pr)
                                 .where(pr.role == Role::name(m_role) and
                                        pr.who == (m_role == Role_Group ? m_groupid : m_who) and
                                        pr.type == Type::name(Type_Object) and
                                        pr.related_table_name == m_related_table )
                                 )
                   )
                  ).front().exists;
    }


    return true;
}

bool Privilege::saveInDb(DB &db, const PrivilegeRow &row) const {
    static constexpr schema::privilege pr;

    try{
        if (db(select(sqlpp::exists(select(pr.role)
                             .from(pr)
                             .where(pr.role == row.role and
                                    pr.who == row.who and
                                    pr.action == row.action and
                                    pr.type == row.type and
                                    pr.related_table_name == row.related_table and
                                    pr.related_object_uid == row.related_uid ) ))).front().exists )
            return true;
        db(sqlpp::postgresql::insert_into(pr)
           .set(pr.role = row.role,
                pr.who = row.who,
                pr.action = row.action,
                pr.type = row.type,
                pr.related_table_name = row.related_table,
                pr.related_object_uid = row.related_uid ));
    }
    catch( const pg_exception &e){
        LOG_DB_EXCEPTION(e);
    }
    return true;
}

}
