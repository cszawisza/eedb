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

//TEST_F(ImplementedActionTest, checkIfExist){

//}

//TEST_F(ImplementedActionTest, createNew){

//}

