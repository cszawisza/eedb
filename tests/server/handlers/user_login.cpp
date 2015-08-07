#include "gtest/gtest.h"

#include <sqlpp11/sqlpp11.h>
#include "core/user.h"
#include <core/database/idatabase.h>
#include <memory>

#include "TestCommon.hpp"

#include "sql_schema/t_users.h"
#include "sql_schema/t_user_history.h"

using namespace test;

class userLoginTest : public ::testing::Test
{
public:
   userLoginTest() {
        db.start_transaction();

       pb::MsgUserRequest_Add add;
       add.mutable_basic()->set_name("USER_NAME");
       add.mutable_basic()->set_email("EMAIL@asdfg.asdf");
       add.set_password("secret_pass");

       requestAdd(add);
   }

   ~userLoginTest(){
        db.rollback_transaction(false);
   }

   MsgUserResponse_Reply requestAdd( pb::MsgUserRequest_Add &msg){
       pb::ClientRequest req;

       auto userReq = req.mutable_msguserreq();
       userReq->mutable_add()->CopyFrom(msg);

       handler.process(db, req);

       return handler.getLastResponse().msguserres().code(0);
   }

   MsgUserResponse_Reply requestLogin( pb::MsgUserRequest_Login &msg){
       pb::ClientRequest req;

       auto userReq = req.mutable_msguserreq();
       userReq->mutable_login()->CopyFrom(msg);

       handler.process(db, req);

       return handler.getLastResponse().msguserres().code(0);
   }
    DB db;
   eedb::handlers::User handler;
};


TEST_F(userLoginTest, badCredentials){
    {
        pb::MsgUserRequest_Login login;
        login.mutable_cred()->set_name("BAD_NAME");
        login.set_password("secret_pass");

        auto res = requestLogin(login);

        EXPECT_EQ(MsgUserResponse_Reply_UserDontExist, res);
        handler.clear();
    }

    {
        pb::MsgUserRequest_Login login;
        login.mutable_cred()->set_email("BAD_EMAIL");
        login.set_password("secret_pass");

        auto res = requestLogin(login);

        EXPECT_EQ(MsgUserResponse_Reply_UserDontExist, res);
        handler.clear();
    }

    {
        pb::MsgUserRequest_Login login;
        login.mutable_cred()->set_email("aaa' OR TRUE -- "); // simple sql injection
        login.set_password("aaa\\' OR TRUE -- ");

        auto res = requestLogin(login);

        EXPECT_EQ(MsgUserResponse_Reply_UserDontExist, res);
        handler.clear();
    }

    {
        pb::MsgUserRequest_Login login;
        login.mutable_cred()->set_email("EMAIL@asdfg.asdf");
        login.set_password("bad_pass");

        auto res = requestLogin(login);

        EXPECT_EQ(MsgUserResponse_Reply_LoginDeny, res);
        handler.clear();
    }

    {
        pb::MsgUserRequest_Login login;
        login.mutable_cred()->set_name("USER_NAME");
        login.set_password("bad_pass");

        auto res = requestLogin(login);

        EXPECT_EQ(MsgUserResponse_Reply_LoginDeny, res);
        handler.clear();
    }
}


TEST_F(userLoginTest, goodCredentials){
    {
        pb::MsgUserRequest_Login login;
        login.mutable_cred()->set_name("USER_NAME");
        login.set_password("secret_pass");

        auto res = requestLogin(login);

        EXPECT_EQ(MsgUserResponse_Reply_LoginPass, res);
        handler.clear();
    }

    {
        pb::MsgUserRequest_Login login;
        login.mutable_cred()->set_email("EMAIL@asdfg.asdf");
        login.set_password("secret_pass");

        EXPECT_EQ(MsgUserResponse_Reply_LoginPass, requestLogin(login));
        handler.clear();
    }
}

TEST_F(userLoginTest, doubleLogin){
    {
        pb::MsgUserRequest_Login login;
        login.mutable_cred()->set_name("USER_NAME");
        login.set_password("secret_pass");

        EXPECT_EQ(MsgUserResponse_Reply_LoginPass, requestLogin(login));
        EXPECT_EQ(MsgUserResponse_Reply_UserOnline, requestLogin(login));
    }
}
