#include <sqlpp11/postgresql/pgexception.h>
#include "spdlog/spdlog.h"

#define LOG_DB_EXCEPTION(e)\
if(e.code().pgClass().isError())\
    LOG_DB_ERROR(e);\
else{\
    LOG_DB_WARNING(e); \
}


#define LOG_DB_ERROR(e) LogDbError(e, __PRETTY_FUNCTION__ )
inline void LogDbError(const sqlpp::postgresql::pg_exception &e, const char* function){
    spdlog::get("Server")->error("{}: {}", function, e.what() );
}

#define LOG_DB_WARNING(e) LogDbWarning(e, __PRETTY_FUNCTION__ )
inline void LogDbWarning(const sqlpp::postgresql::pg_exception &e, const char* function){
    spdlog::get("Server")->warn("{}: {}", function, e.what() );
}
