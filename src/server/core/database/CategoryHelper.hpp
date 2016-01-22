#pragma once

#include <sqlpp11/sqlpp11.h>
#include <sql_schema/shelfs.h>
#include <sql_schema/categories.h>

#include "idatabase.h"
#include <boost/optional.hpp>


using boost::optional;

namespace eedb{
namespace db{

class CategoryHelper {
public:

    static auto insert_into( ){
        constexpr schema::categories u;
        return sqlpp::postgresql::insert_into(u);
    }

    static optional<int64_t> rootCategoryId(DB &db);

//    static optional<uint64_t> addCategory(DB &db, const CategoryData &category);
};

}
}
