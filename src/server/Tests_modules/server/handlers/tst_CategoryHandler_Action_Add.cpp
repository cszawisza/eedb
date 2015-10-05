#include "gtest/gtest.h"

#include <core/database/idatabase.h>
#include <core/database/CategoryHelper.hpp>

#include <core/category.hpp>

#include "TestCommon.hpp"

using namespace eedb::db;
using namespace test;


class CategoryHelpertest : public ::testing::Test
{
public:

    CategoryHelpertest(){
        db.start_transaction();

        test::addUser(db, "xxxxxxx");
        handler.setUserData(test::login(db, "xxxxxxx")); // go online
    }

    ~CategoryHelpertest(){
        db.rollback_transaction(false);
    }

    ServerResponse runMessageHandlerProcess(){
        ClientRequest cliReq;
        auto catReq = cliReq.mutable_categoryreq();
        catReq->mutable_add()->MergeFrom(addMsg);

        handler.process(db, cliReq );

        return handler.getLastResponse();
    }

    void upgradeUserPrivileges(){
        auth::Privilege priv;
        constexpr schema::t_categories c;
        constexpr schema::users u;
        priv.giveGroup(auth::GROUP_categories).privilegeFor("write").forTable(c).force_save(db);
        db(update(u).set(u.acl_group = sqlpp::verbatim<sqlpp::integer>( std::string(tableName<decltype(u)>()) + ".acl_group | (1<<3)" )).where(u.name == "xxxxxxx" ));
    }

protected:
    DB db;
    CategoryReq_Add addMsg;
    eedb::handlers::Category handler;
};

TEST_F(CategoryHelpertest, userWithDefaultPermsShoudCannotAddCategory ){
    addMsg.set_name("New Category");
    addMsg.set_parent_id(CategoryHelper::rootCategoryId(db).get_value_or(0));
    ServerResponse res = runMessageHandlerProcess();

    ASSERT_TRUE ( res.has_code() );
    ASSERT_EQ   ( ServerError::Error_AccesDeny, res.code());
    EXPECT_FALSE(res.has_categoryres());
}

TEST_F(CategoryHelpertest, addCategory){
    upgradeUserPrivileges();
    addMsg.set_name("New Category");
    addMsg.set_parent_id(CategoryHelper::rootCategoryId(db).get_value_or(0));
    ServerResponse res = runMessageHandlerProcess();

    ASSERT_TRUE ( res.has_categoryres() );

    CategoryRes catRes = res.categoryres();
    EXPECT_EQ   ( CategoryRes_Replay_AddSuccesful, catRes.code());
    EXPECT_FALSE(catRes.has_id());
    EXPECT_FALSE(catRes.has_description());
    EXPECT_FALSE(catRes.has_name());
    EXPECT_FALSE(catRes.has_parent_id());
}

TEST_F(CategoryHelpertest, addCategoryReturnId){
    upgradeUserPrivileges();
    addMsg.set_name("New Category");
    addMsg.set_parent_id(CategoryHelper::rootCategoryId(db).get_value_or(0));

    addMsg.set_returningid(true);
    ServerResponse res = runMessageHandlerProcess();

    ASSERT_TRUE ( res.has_categoryres() );

    CategoryRes catRes = res.categoryres();
    EXPECT_EQ   ( CategoryRes_Replay_AddSuccesful, catRes.code());
    EXPECT_TRUE (catRes.has_id());
    EXPECT_FALSE(catRes.has_description());
    EXPECT_FALSE(catRes.has_name());
    EXPECT_FALSE(catRes.has_parent_id());
}

TEST_F(CategoryHelpertest, doubleInsertShouldFail){
    upgradeUserPrivileges();
    addMsg.set_name("New Category");
    addMsg.set_parent_id(CategoryHelper::rootCategoryId(db).get_value_or(0));

    ServerResponse res1 = runMessageHandlerProcess();
    ServerResponse res2 = runMessageHandlerProcess();

    ASSERT_TRUE ( res1.has_categoryres() );
    ASSERT_TRUE ( res2.has_categoryres() );

    CategoryRes catRes = res1.categoryres();
    EXPECT_EQ   ( CategoryRes_Replay_AddSuccesful, catRes.code());

    catRes = res2.categoryres();
    EXPECT_EQ   ( CategoryRes_Replay_CategoryExists, catRes.code());
}

