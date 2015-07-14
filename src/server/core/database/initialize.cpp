#include "initialize.hpp"

#include "sql_schema/t_system_info.h"
#include "sql_schema/t_users.h"

#include "../user.h"
#include "../auth/privilege.hpp"

using auth::Action;
namespace eedb{

int DBInitialize::initializeDB(DB &db)
{
    if(! rootExists(db)){
        pb::MsgUserRequest_Add add;
        auto acl  = add.mutable_acl();
        auto basic= add.mutable_basic();

        acl->set_owner( 1 );
        acl->set_group( 1 );

        basic->set_name("ROOT");
        basic->set_description("Root user");
        basic->set_email("b.w@linux.pl");

        add.set_password("admin_eedb");
        handlers::User::insertUser(db, add);
    }

    insertActionIfNotExists(db, Action( "stat" , auth::Object ));
    insertActionIfNotExists(db, Action( "stat" , auth::Table ));
    insertActionIfNotExists(db, Action( "chmod" , auth::Object ));
    insertActionIfNotExists(db, Action( "chmod" , auth::Table ));
    insertActionIfNotExists(db, Action( "chgrp" , auth::Object ));
    insertActionIfNotExists(db, Action( "chgrp" , auth::Table ));
    insertActionIfNotExists(db, Action( "chown" , auth::Object ));
    insertActionIfNotExists(db, Action( "chown" , auth::Table ));
    insertActionIfNotExists(db, Action( "view_acl" , auth::Object ));
    insertActionIfNotExists(db, Action( "view_acl" , auth::Table ));
    insertActionIfNotExists(db, Action( "read" , auth::Object ));
    insertActionIfNotExists(db, Action( "write" , auth::Object ));
    insertActionIfNotExists(db, Action( "delete" , auth::Object ));
    insertActionIfNotExists(db, Action( "read" , auth::Table ));
    insertActionIfNotExists(db, Action( "write" , auth::Table ));
    insertActionIfNotExists(db, Action( "login" , auth::Object ));
    insertActionIfNotExists(db, Action( "update_passwd" , auth::Object ));

    insertImplementedActionIfNotExists(db, auth::ImplementedAction("login",auth::State_Normal,"t_users"));
    insertImplementedActionIfNotExists(db, auth::ImplementedAction("update_passwd",auth::State_Normal,"t_users"));
    insertImplementedActionIfNotExists(db, auth::ImplementedAction("read",auth::State_Normal,"t_users"));
    insertImplementedActionIfNotExists(db, auth::ImplementedAction("write",auth::State_Normal,"t_users"));
    insertImplementedActionIfNotExists(db, auth::ImplementedAction("delete",auth::State_Normal,"t_users"));
    insertImplementedActionIfNotExists(db, auth::ImplementedAction("read",auth::State_Normal,"t_files"));
    insertImplementedActionIfNotExists(db, auth::ImplementedAction("write",auth::State_Normal,"t_files"));
    insertImplementedActionIfNotExists(db, auth::ImplementedAction("delete",auth::State_Normal,"t_files"));
}

bool DBInitialize::rootExists(DB &db) const
{
    static constexpr schema::t_users u;
    return db(sqlpp::select(exists(sqlpp::select(u.c_uid).from(u).where(u.c_name == "ROOT")))).front().exists;
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

}
