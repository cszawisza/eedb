#include <gtest/gtest.h>
#include "core/idatabase.h"
#include "core/auth/implementedaction.hpp"

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

TEST_F(ImplementedActionTest, checkIfExist){
//    Action act ("new_action_not_existing_in_db", Object );

//    EXPECT_FALSE( act.actionExists(db));
}

TEST_F(ImplementedActionTest, createNewAction){
//    Action act ("new_action", Object );

//    EXPECT_TRUE( act.save(db) );
//    EXPECT_TRUE( act.actionExists(db) );
}

