#include "gtest/gtest.h"

#include <sqlpp11/sqlpp11.h>
#include "core/user.h"
#include <core/idatabase.h>
#include <memory>

#include "../../common.h"

class userCreateTest : public ::testing::Test
{
public:
    userCreateTest() {
        schema::t_users u;
        createBackup(u);
    }

    ~userCreateTest(){
        schema::t_users u;
        restoreBackup(u);
    }

    const ResponseCode &sendRequest( pb::MsgUserRequest_Add &msg){
        protbuf::ClientRequest req;

        auto userReq = req.mutable_msguserreq();
        userReq->mutable_add()->CopyFrom(msg);

        handler.process(req);

        return handler.getLastResponse().codes(0);
    }

    eedb::handlers::User handler;
};

TEST_F( userCreateTest, user_no_name_and_email){
    pb::MsgUserRequest_Add req;

    req.set_password("passwd");
    auto res = sendRequest(req);
    EXPECT_TRUE(res.error());

}

TEST_F( userCreateTest, user_no_email){
    pb::MsgUserRequest_Add req;

    req.set_password("passwd");
    req.mutable_basic()->set_name("Test_user_asdf");
    auto res = sendRequest(req);
    EXPECT_TRUE(res.error());
}

TEST_F( userCreateTest, create_withBasicData ){
    pb::MsgUserRequest_Add req;

    req.set_password("passwd");
    req.mutable_basic()->set_name("Test_user_asdf");
    req.mutable_basic()->set_email("TestUser@user.uu");
    auto res = sendRequest(req);
    EXPECT_FALSE(res.error());
}

TEST_F( userCreateTest, user_name_to_long ){
    pb::MsgUserRequest_Add req;

    req.set_password("passwd");
    req.mutable_basic()->set_name( random_string(73) );
    req.mutable_basic()->set_email( random_string(10) + "@user.uu");
    auto res = sendRequest(req);
    EXPECT_TRUE(res.error());
}

TEST_F( userCreateTest, full_data ){
    pb::MsgUserRequest_Add add_msg;

    auto basic = add_msg.mutable_basic();
    auto det   = add_msg.mutable_details();
    add_msg.set_password("passwd");
    basic->set_name( random_string(10) );
    basic->set_email( random_string(10) + "@user.uu");
    det->set_address( random_string(100) );
    det->set_phone_number( random_string(10) );
    basic->set_description( random_string(10000) );
    basic->set_avatar( random_string(80*1000) ); // a text base representation of file

    auto res = sendRequest(add_msg);

    EXPECT_FALSE(res.error());
}
