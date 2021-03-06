#pragma once
#include "sqlpp11/sqlpp11.h"

namespace sqlpp {
inline auto toBool(bool val) -> sqlpp::verbatim_t<sqlpp::boolean>{
    return sqlpp::verbatim<sqlpp::boolean>( val ? "TRUE " : "FALSE " );
}

template<typename T>
inline constexpr const char * tableName(){
    return sqlpp::name_of<T>::char_ptr();
}
template<typename T>
inline constexpr const char * tableName(const T &tab){
    return sqlpp::name_of<decltype(tab)>::char_ptr();
}

template<typename T>
inline constexpr const char * fieldName(){
    return sqlpp::name_of<T>::char_ptr();
}

}
