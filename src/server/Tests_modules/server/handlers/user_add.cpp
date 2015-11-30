#include "gtest/gtest.h"
#include "TestCommon.hpp"

using namespace test;

class userCreateTest : public ::testing::Test
{
public:
    userCreateTest() {
        db.start_transaction();
    }

    ~userCreateTest(){
        db.rollback_transaction(false);
    }

    UserRes_Reply sendRequest( pb::UserReq_Add &msg){
        pb::ClientRequest req;

        auto userReq = req.mutable_userreq();
        userReq->mutable_add()->CopyFrom(msg);

        handler.process(db, req);

        return handler.getLastResponse().userres().code(0);
    }

    DB db;
    eedb::pu::UserPU handler;
};

TEST_F( userCreateTest, user_no_name_and_email){
    pb::UserReq_Add req;

    req.set_password("passwd");
    auto res = sendRequest(req);
    EXPECT_EQ( UserRes_Reply_MissingRequiredField, res );
}

TEST_F( userCreateTest, user_no_email){
    pb::UserReq_Add req;

    req.set_password("passwd");
    req.mutable_basic()->set_nickname("Test_user_asdf");
    auto res = sendRequest(req);
    EXPECT_EQ(UserRes_Reply_MissingRequiredField, res);
}

TEST_F( userCreateTest, create_withBasicData ){
    pb::UserReq_Add req;

    req.set_password("passwd");
    req.mutable_basic()->set_nickname("Test_user_asdf");
    req.mutable_basic()->set_email("TestUser@user.uu");
    auto res = sendRequest(req);
    EXPECT_EQ(UserRes_Reply_UserAddOk, res);
}

TEST_F( userCreateTest, user_name_to_long ){
    pb::UserReq_Add req;

    req.set_password("passwd");
    req.mutable_basic()->set_nickname( random_string(73) );
    req.mutable_basic()->set_email( random_string(10) + "@user.uu");
    auto res = sendRequest(req);
    EXPECT_EQ(UserRes_Reply_UserNameToLong, res);
}

TEST_F( userCreateTest, user_duplicated ){
    pb::UserReq_Add req;

    string name = "RANDOM_USER_NAME";
    string email= "RANDOM_USER_NAME@email.com";

    req.set_password("passwd");
    req.mutable_basic()->set_nickname( name );
    req.mutable_basic()->set_email( email );
    auto res = sendRequest(req);
    EXPECT_EQ(UserRes_Reply_UserAddOk, res);

    req.mutable_basic()->set_nickname("different_name");
    res = sendRequest(req);
    EXPECT_EQ(UserRes_Reply_UserAlreadyExists, res); // different name but the same email

    req.mutable_basic()->set_nickname( name );
    req.mutable_basic()->set_email( "DIFFERENTEMAIL@asdfg.sa");
    res = sendRequest(req);
    EXPECT_EQ(UserRes_Reply_UserAlreadyExists, res); // different email but the same name
}

TEST_F( userCreateTest, full_data ){
    pb::UserReq_Add add_msg;

    auto basic = add_msg.mutable_basic();
    auto det   = add_msg.mutable_details();
    add_msg.set_password("passwd");
    basic->set_nickname( random_string(10) );
    basic->set_email( random_string(10) + "@user.uu");
    det->set_address( random_string(100) );
    det->set_phone_number( random_string(10) );
    basic->set_description( random_string(1000) );
    basic->set_avatar( random_string(1000) );

    auto res = sendRequest(add_msg);

    EXPECT_EQ(UserRes_Reply_UserAddOk, res);
}
