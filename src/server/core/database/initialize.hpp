#pragma once

#include <sqlpp11/sqlpp11.h>
#include "idatabase.h"
#include "auth/action.hpp"
#include "auth/implementedaction.hpp"
#include "auth/privilege.hpp"

#define DB_VERSION 10


namespace eedb {

class DBInitialize{
public:
    int getDBSchemaVersion(DB &db);
    int initializeDB(DB &db);
    int updateDB(DB &db, int version);

private:
    bool rootExists(DB &db) const;
    bool rootCategoryExists(DB &db) const;

    void insertActionIfNotExists(DB &db, auth::Action action ) const;
    void insertImplementedActionIfNotExists(DB &db, auth::ImplementedAction ia) const;
    void insertPrivilegeIfNotExists(DB &db, auth::Privilege pr) const;
};

}
