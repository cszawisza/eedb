#include <gtest/gtest.h>

#include "core/idatabase.h"
#include "core/auth/implementedaction.hpp"

#include "sql_schema/t_users.h"
using namespace auth;

class ImplementedActionTest : public testing::Test
{
public:
    ImplementedActionTest(){
        db.start_transaction();
    }

    ~ImplementedActionTest(){
        db.rollback_transaction(false);
    }

    DB db;
};

TEST_F(ImplementedActionTest, ctor){
    ImplementedAction action1;
    ImplementedAction action2("new_implemented_action");
    ImplementedAction action3("new_implemented_action", auth::State_Normal);

    action1.setRelatedTable<schema::t_users>();
    action2.setRelatedTable<schema::t_users>();
    action3.setRelatedTable<schema::t_users>();

    action1.setTitle("new_implemented_action");
    action1.setStatus(auth::State_Normal);

    EXPECT_EQ("new_implemented_action", action1.title() );
    EXPECT_EQ(auth::State_Normal, action1.status());

    EXPECT_EQ(action1.title() , action2.title() );
    EXPECT_EQ(action1.status(), action2.status() );

    EXPECT_EQ(action1.title() , action3.title() );
    EXPECT_EQ(action1.status(), action3.status() );
}

TEST_F(ImplementedActionTest, createNew){
    ImplementedAction action("new_implemented_action");
    action.setRelatedTable<schema::t_users>();

    EXPECT_TRUE( action.save(db) );
}

TEST_F(ImplementedActionTest, notExists){
    ImplementedAction action("new_implemented_action");
    action.setRelatedTable<schema::t_users>();

    EXPECT_FALSE( action.exists(db) );
}

TEST_F(ImplementedActionTest, createNewAndCheckIfExists){
    ImplementedAction action("new_implemented_action");
    action.setRelatedTable<schema::t_users>();

    EXPECT_TRUE( action.save(db) );
    EXPECT_TRUE( action.exists(db) );
}

TEST_F(ImplementedActionTest, differentStatuses ){
    ImplementedAction action1("new_implemented_action", auth::State_Normal );
    ImplementedAction action2("new_implemented_action", auth::State_Deleted);

    action1.setRelatedTable<schema::t_users>();
    action2.setRelatedTable<schema::t_users>();

    EXPECT_TRUE( action1.save(db) );
    EXPECT_TRUE( action2.save(db) );
}

//TEST_F(ImplementedActionTest, aclCheck ){
//    ImplementedAction action1("read", auth::State_Normal );

//    action1.setRelatedTable<schema::t_users>();

//    EXPECT_TRUE( action1.save(db) );
//}
