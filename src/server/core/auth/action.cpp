#include "action.hpp"

#include <iostream>

#include "utils/sqlpp_helper.hpp"
#include "sql_schema/t_action.h"

#include "database/idatabase.h"
#include "utils/LogUtils.hpp"

using sqlpp::toBool;
using sqlpp::postgresql::pg_exception;

namespace auth{

bool Action::save(DB &db){
    static constexpr schema::t_action a;
    bool ok = false;
    try{
        db(sqlpp::postgresql::insert_into(a).set(
               a.c_title = title(),
               a.c_apply_object = toBool(applyToObject())
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
    static constexpr schema::t_action a;
    auto exist = false;
    try{
        exist = db(select(
                       sqlpp::exists(
                           select(a.c_title)
                           .from(a)
                           .where(a.c_title == title() and
                                  a.c_apply_object == toBool(applyToObject())
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
