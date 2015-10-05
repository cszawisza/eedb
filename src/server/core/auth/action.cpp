#include "action.hpp"

#include <iostream>

#include "utils/sqlpp_helper.hpp"
#include "sql_schema/action.h"

#include "database/idatabase.h"
#include "utils/LogUtils.hpp"

using sqlpp::toBool;
using sqlpp::postgresql::pg_exception;

namespace auth{

bool Action::save(DB &db){
    static constexpr schema::action a;
    bool ok = false;
    try{
        db(sqlpp::postgresql::insert_into(a).set(
               a.title = title(),
               a.apply_object = toBool(applyToObject())
                ));
        ok = true;
    }
    catch( const pg_exception &e ){
        LOG_DB_EXCEPTION(e);
    }
    return ok;
}

bool Action::exists(DB &db) const
{
    static constexpr schema::action a;
    auto exist = false;
    try{
        exist = db(select(
                       sqlpp::exists(
                           select(a.title)
                           .from(a)
                           .where(a.title == title() and
                                  a.apply_object == toBool(applyToObject())
                                  )
                           )
                       )
                   ).front().exists;
    }
    catch( const pg_exception &e ){
        LOG_DB_EXCEPTION(e);
    }

    return exist;
}

}
