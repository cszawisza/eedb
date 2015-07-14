#include "action.hpp"

#include <iostream>

#include "utils/sqlpp_helper.hpp"
#include "sql_schema/t_action.h"

#include "database/idatabase.h"

using sqlpp::toBool;

namespace auth{

bool Action::save(DB &db){
    static constexpr schema::t_action a;
    bool ok = false;
    try{
        db(insert_into(a).set(
               a.c_title = title(),
               a.c_apply_object = toBool(applyToObject())
                ));
        ok = true;
    }
    catch(sqlpp::exception e){
        ///TODO log
        std::cout << e.what();
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
    catch(sqlpp::exception e){
        std::cout << e.what();
    }

    return exist;
}

}
