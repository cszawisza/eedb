#include "privilege.hpp"
#include "utils/CTcrc32.hpp"

using std::string;
namespace auth {

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

}
