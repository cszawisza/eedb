#pragma once

#include <sqlpp11/sqlpp11.h>

#include "idatabase.h"

#include <sql_schema/t_shelfs.h>
#include <sql_schema/t_categories.h>

#include <boost/optional.hpp>

#include "category.pb.h"


using boost::optional;

namespace eedb{
namespace db{

class CategoryHelper {
public:

    static auto insert_into( ){
        constexpr schema::t_categories u;
        return sqlpp::postgresql::insert_into(u);
    }

    static optional<int64_t> rootCategoryId(DB &db){
        constexpr schema::t_categories cat;
        // only root category can have null parent
        auto result = db(sqlpp::select(cat.c_uid).from(cat).where(cat.c_parent_category_id.is_null() ).limit(1));
        if(result.empty())
            return boost::none;
        return optional<int64_t>(result.front().c_uid);
    }

//    static optional<uint64_t> addCategory(DB &db, const CategoryData &category);
};

}
}
