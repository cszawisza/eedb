#include "gtest/gtest.h"

#include <core/database/idatabase.h>
#include <core/database/CategoryHelper.hpp>

#include <core/category.hpp>

#include "TestCommon.hpp"

using namespace eedb::db;
using namespace test;


class CategoryHelperGetTest : public ::testing::Test
{
public:

    CategoryHelperGetTest(){
        db.start_transaction();

        test::addUser(db, "xxxxxxx");
        handler.setUserData(test::login(db, "xxxxxxx")); // go online
    }

    ~CategoryHelperGetTest(){
        db.rollback_transaction(false);
    }

    void insertTestGroups(){
        constexpr schema::t_categories c;
        auto rootCat = db(select(c.uid).from(c).where(c.c_parent_category_id.is_null())).front().uid;
        auto cat1id = db(sqlpp::postgresql::insert_into(c).set(c.name = "cat_1_1", c.c_parent_category_id = rootCat).returning(c.uid)).front().uid;
        db(sqlpp::postgresql::insert_into(c).set(c.name = "cat_2_1", c.c_parent_category_id = cat1id));
        db(sqlpp::postgresql::insert_into(c).set(c.name = "cat_2_2", c.c_parent_category_id = cat1id));
    }

    ServerResponse runMessageHandlerProcess(){
        ClientRequest cliReq;
        auto catReq = cliReq.mutable_categoryreq();
        catReq->mutable_get()->MergeFrom(getMsg);

        handler.process( db, cliReq );

        return handler.getLastResponse();
    }

    void upgradeUserPrivileges(){
        auth::Privilege priv;
        constexpr schema::t_categories c;
        constexpr schema::users u;
        priv.giveGroup(auth::GROUP_categories).privilegeFor("write").forTable(c).force_save(db);
        db(update(u).set(u.acl_group = sqlpp::verbatim<sqlpp::integer>( std::string(tableName<decltype(u)>()) + ".acl_group | (1<<3)" )).where(u.name == "xxxxxxx" )); ///FIXME
    }

protected:
    DB db;
    CategoryReq_Get getMsg;
    eedb::handlers::Category handler;
};

TEST_F(CategoryHelperGetTest, userWithDefaultPermsShoudCanGetCategory ){
    insertTestGroups();
    getMsg.set_get_ids(true);
    getMsg.set_get_name(true);
    getMsg.set_get_description(true);
    getMsg.mutable_where()->set_all_groups(true);

    ServerResponse res = runMessageHandlerProcess();

    ASSERT_FALSE( res.has_code() );
    ASSERT_TRUE ( res.has_categoryres() );
    EXPECT_GE( handler.responseCount(), 3);
}
