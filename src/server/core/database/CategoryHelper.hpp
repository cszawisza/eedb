#pragma once

#include <sqlpp11/sqlpp11.h>

#include "idatabase.h"

#include <sql_schema/t_shelfs.h>
#include <sql_schema/t_categories.h>

#include <boost/optional.hpp>


using boost::optional;

namespace eedb{
namespace db{

struct CategoryData {
    optional<string> name;
};

class CategoryHelper {
public:

    static auto insert_into( ){
        constexpr schema::t_categories u;
        return sqlpp::postgresql::insert_into(u);
    }

    static optional<uint64_t> addCategory(DB &db, const CategoryData &category);
};

}
}
