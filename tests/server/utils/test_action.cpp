#include <gtest/gtest.h>
#include "core/idatabase.h"
#include "core/auth/action.hpp"

using namespace auth;

class ActionTest : public testing::Test
{
public:
    ActionTest(){
        db.start_transaction();
    }

    ~ActionTest(){
        db.rollback_transaction(false);
    }

    DB db;
};

TEST_F(ActionTest, checkIfExist){
    Action act ("new_action_not_existing_in_db", Object );

    EXPECT_FALSE( act.actionExists(db));
}

TEST_F(ActionTest, createNewAction){
    Action act ("new_action", Object );

    EXPECT_TRUE( act.save(db) );
    EXPECT_TRUE( act.actionExists(db) );
}

//TEST_F(ActionTest, doubleSaving){
//    Action act ("new_action", Object );

//    EXPECT_TRUE( act.save(db) );
//    EXPECT_FALSE( act.save(db) );
//}
