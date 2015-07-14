#include "implementedaction.hpp"
#include "action.hpp"
#include "core/idatabase.h"

namespace auth {

bool ImplementedAction::save(DB &db){
    static constexpr schema::t_implemented_action ia;
    bool ok = false;
    try{
        db(insert_into(ia).set(ia.c_table = m_tablename, ia.c_action = m_title, ia.c_status = (int)m_status ));
        ok = true;
    }
    catch(sqlpp::exception e){
        ///TODO log exception
        std::cout << e.what();
    }

    return ok;
}

bool ImplementedAction::exists(DB &db) const {
    static constexpr schema::t_implemented_action ia;
    return db(sqlpp::select(sqlpp::exists(sqlpp::select(ia.c_action)
                                          .from(ia)
                                          .where(ia.c_table == m_tablename and ia.c_action == m_title and ia.c_status == (int)m_status )
                                          )
                            )
              ).front().exists;
}

}
