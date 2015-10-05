#include "initialize.hpp"

#include "sql_schema/system_info.h"
#include "sql_schema/users.h"

#include "../user.h"
#include "../auth/privilege.hpp"

#include "database/UserHelper.hpp"

#include "sql_schema/t_inventories.h"
#include "sql_schema/t_shelfs.h"
#include "sql_schema/t_categories.h"


using auth::Action;
using auth::Groups;

using eedb::db::UserHelper;

namespace eedb{

int DBInitialize::initializeDB(DB &db)
{
    static constexpr schema::t_categories cat;
    static constexpr schema::t_inventories inv;
    static constexpr schema::t_shelfs sh;

    if(! rootExists(db)){
        pb::UserReq_Add add;
        auto acl  = add.mutable_acl();
        auto basic= add.mutable_basic();

        acl->set_owner( 1 );
        acl->set_group( 1 );

        basic->set_name("ROOT");
        basic->set_description("Root user");
        basic->set_email("b.w@linux.pl");

        add.set_password("admin_eedb");
        UserHelper::insertUser(db, add);
    }

    if(! rootCategoryExists(db)){
        db(sqlpp::postgresql::insert_into(cat).set(cat.name = "Root group"));
    }

    auth::Privilege priv;

    priv.giveGroup( auth::GROUP_users | auth::GROUP_inventories )
            .privilegeFor("read")
            .forTable(inv)
            .force_save(db);

    priv.giveGroup( auth::GROUP_inventories )
            .privilegeFor("write")
            .forTable(inv).
            force_save(db);

    priv.giveGroup( auth::GROUP_users | auth::GROUP_inventories  )
            .privilegeFor("write")
            .forTable(sh)
            .force_save(db);

    priv.giveGroup( auth::GROUP_inventories )
            .privilegeFor("write")
            .forTable(sh)
            .force_save(db);

    priv.giveGroup( auth::GROUP_users )
            .privilegeFor("read")
            .forTable(cat)
            .force_save(db);

}

bool DBInitialize::rootExists(DB &db) const
{
    static constexpr schema::users u;
    return db(sqlpp::select(exists(sqlpp::select(u.uid).from(u).where(u.name == "ROOT")))).front().exists;
}

bool DBInitialize::rootCategoryExists(DB &db) const
{
    static constexpr schema::t_categories c;
    return db(sqlpp::select(exists(sqlpp::select(c.uid).from(c).where(c.c_parent_category_id.is_null())))).front().exists;
}

void DBInitialize::insertActionIfNotExists(DB &db, auth::Action action) const
{
    if(!action.exists(db))
        action.save(db);
}

void DBInitialize::insertImplementedActionIfNotExists(DB &db, auth::ImplementedAction ia) const
{
    if(!ia.exists(db))
        ia.save(db);
}

void DBInitialize::insertPrivilegeIfNotExists(DB &db, auth::Privilege pr) const
{
    if(!pr.exists(db))
        pr.force_save(db);
}

}
