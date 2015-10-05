#include "implementedaction.hpp"
#include "action.hpp"
#include "database/idatabase.h"
#include "utils/LogUtils.hpp"

using sqlpp::postgresql::pg_exception;

namespace auth {

bool ImplementedAction::save(DB &db){
    static constexpr schema::implemented_action ia;
    bool ok = false;
    try{
        db(sqlpp::postgresql::insert_into(ia).set(ia.table_name = m_tablename, ia.action = m_title, ia.status = (int)m_status ));
        ok = true;
    }
    catch( const pg_exception &e ){
        LOG_DB_EXCEPTION(e);
    }

    return ok;
}

bool ImplementedAction::exists(DB &db) const {
    static constexpr schema::implemented_action ia;
    return db(sqlpp::select(sqlpp::exists(sqlpp::select(ia.action)
                                          .from(ia)
                                          .where(ia.table_name == m_tablename and ia.action == m_title and ia.status == (int)m_status )
                                          )
                            )
              ).front().exists;
}
}
