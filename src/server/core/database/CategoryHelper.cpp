#include "CategoryHelper.hpp"


//optional<uint64_t> eedb::db::CategoryHelper::addCategory(DB &db, const CategoryData &category)
//{
//    constexpr schema::categories c;
//    db(sqlpp::postgresql::insert_into(c).set(c.name = category.name) );
//}


optional<int64_t> eedb::db::CategoryHelper::rootCategoryId(DB &db){
    constexpr schema::categories cat;
    // only root category can have null parent
    auto result = db(sqlpp::select(cat.uid).from(cat).where(cat.parent_category_id.is_null() ).limit(1));
    if(result.empty())
        return boost::none;
    return optional<int64_t>(result.front().uid);
}
