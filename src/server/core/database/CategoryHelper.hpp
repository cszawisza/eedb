#pragma once

#include <sqlpp11/sqlpp11.h>

#include "idatabase.h"

#include <sql_schema/shelfs.h>
#include <sql_schema/categories.h>

#include <boost/optional.hpp>

#include "category.pb.h"


using boost::optional;

namespace eedb{
namespace db{

class CategoryHelper {
public:

    static auto insert_into( ){
        constexpr schema::categories u;
        return sqlpp::postgresql::insert_into(u);
    }

    static optional<int64_t> rootCategoryId(DB &db){
        constexpr schema::categories cat;
        // only root category can have null parent
        auto result = db(sqlpp::select(cat.uid).from(cat).where(cat.parent_category_id.is_null() ).limit(1));
        if(result.empty())
            return boost::none;
        return optional<int64_t>(result.front().uid);
    }

//    static optional<uint64_t> addCategory(DB &db, const CategoryData &category);
};

}
}
