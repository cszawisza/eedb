#include "action.hpp"
<<<<<<< HEAD
#include <iostream>
=======

>>>>>>> origin/master
#include "utils/sqlpp_helper.hpp"
#include "sql_schema/t_action.h"

#include "../idatabase.h"

<<<<<<< HEAD

using sqlpp::toBool;

=======
>>>>>>> origin/master
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

<<<<<<< HEAD
bool Action::exists(DB &db) const
=======
bool Action::actionExists(DB &db) const
>>>>>>> origin/master
{
    static constexpr schema::t_action a;
    auto exist = false;
    try{
        exist = db(select(
<<<<<<< HEAD
                       sqlpp::exists(
=======
                       exists(
>>>>>>> origin/master
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
