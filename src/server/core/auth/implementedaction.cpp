#include "implementedaction.hpp"
#include "action.hpp"
#include "database/idatabase.h"
#include "utils/LogUtils.hpp"

using sqlpp::postgresql::pg_exception;

namespace auth {

bool ImplementedAction::save(DB &db){
    static constexpr schema::t_implemented_action ia;
    bool ok = false;
    try{
        db(sqlpp::postgresql::insert_into(ia).set(ia.c_table = m_tablename, ia.c_action = m_title, ia.c_status = (int)m_status ));
        ok = true;
    }
    catch( const pg_exception &e ){
        LOG_DB_EXCEPTION(e);
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
