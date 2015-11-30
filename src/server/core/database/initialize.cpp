#include "initialize.hpp"

#include "sql_schema/system_info.h"
#include "sql_schema/users.h"

#include "ProcessingUnits/UserPU.hpp"
#include "../auth/privilege.hpp"

#include "database/UserHelper.hpp"

#include "sql_schema/inventories.h"
#include "sql_schema/shelfs.h"
#include "sql_schema/categories.h"
#include "sql_schema/items.h"


using auth::Action;
using auth::Groups;

using eedb::db::UserHelper;

namespace eedb{

int DBInitialize::initializeDB(DB &db)
{
    static constexpr schema::categories cat;
    static constexpr schema::inventories inv;
    static constexpr schema::shelfs sh;
    static constexpr schema::items i;

    if(! rootExists(db)){
        pb::UserReq_Add add;
        auto stat  = add.mutable_acl();
        auto basic= add.mutable_basic();

        stat->set_owner( 1 );
        stat->set_group( 1 );

        basic->set_nickname("ROOT");
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

    priv.giveGroup(auth::GROUP_users)
            .privilegeFor("add_private_item")
            .forTable(i)
            .force_save(db);

    priv.giveGroup(auth::GROUP_items)
            .privilegeFor("add_public_item")
            .forTable(i)
            .force_save(db);
}

bool DBInitialize::rootExists(DB &db) const
{
    static constexpr schema::users u;
    return db(sqlpp::select(exists(sqlpp::select(u.uid).from(u).where(u.name == "ROOT")))).front().exists;
}

bool DBInitialize::rootCategoryExists(DB &db) const
{
    static constexpr schema::categories c;
    return db(sqlpp::select(exists(sqlpp::select(c.uid).from(c).where(c.parent_category_id.is_null())))).front().exists;
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
