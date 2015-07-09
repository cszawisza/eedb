#include "sqlpp11/sqlpp11.h"

inline auto toBool(bool val) -> sqlpp::verbatim_t<sqlpp::boolean>{
    return sqlpp::verbatim<sqlpp::boolean>( val ? "TRUE " : "FALSE " );
}
