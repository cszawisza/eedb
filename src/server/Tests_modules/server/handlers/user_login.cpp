#include "gtest/gtest.h"

#include <sqlpp11/sqlpp11.h>
#include "core/user.h"
#include <core/database/idatabase.h>
#include <memory>

#include "TestCommon.hpp"

#include "sql_schema/users.h"
#include "sql_schema/user_history.h"

using namespace test;

class userLoginTest : public ::testing::Test
{
public:
   userLoginTest() {
        db.start_transaction();

       pb::UserReq_Add add;
       add.mutable_basic()->set_name("USER_NAME");
       add.mutable_basic()->set_email("EMAIL@asdfg.asdf");
       add.set_password("secret_pass");

       requestAdd(add);
   }

   ~userLoginTest(){
        db.rollback_transaction(false);
   }

   UserRes_Reply requestAdd( pb::UserReq_Add &msg){
       pb::ClientRequest req;

       auto userReq = req.mutable_userreq();
       userReq->mutable_add()->CopyFrom(msg);

       handler.process(db, req);

       return handler.getLastResponse().userres().code(0);
   }

   UserRes_Reply requestLogin( pb::UserReq_Login &msg){
       pb::ClientRequest req;

       auto userReq = req.mutable_userreq();
       userReq->mutable_login()->CopyFrom(msg);

       handler.process(db, req);

       return handler.getLastResponse().userres().code(0);
   }
    DB db;
   eedb::handlers::User handler;
};


TEST_F(userLoginTest, badCredentials){
    {
        pb::UserReq_Login login;
        login.mutable_cred()->set_name("BAD_NAME");
        login.set_password("secret_pass");

        auto res = requestLogin(login);

        EXPECT_EQ(UserRes_Reply_UserDontExist, res);
        handler.clear();
    }

    {
        pb::UserReq_Login login;
        login.mutable_cred()->set_email("BAD_EMAIL");
        login.set_password("secret_pass");

        auto res = requestLogin(login);

        EXPECT_EQ(UserRes_Reply_UserDontExist, res);
        handler.clear();
    }

    {
        pb::UserReq_Login login;
        login.mutable_cred()->set_email("aaa' OR TRUE -- "); // simple sql injection
        login.set_password("aaa\\' OR TRUE -- ");

        auto res = requestLogin(login);

        EXPECT_EQ(UserRes_Reply_UserDontExist, res);
        handler.clear();
    }

    {
        pb::UserReq_Login login;
        login.mutable_cred()->set_email("EMAIL@asdfg.asdf");
        login.set_password("bad_pass");

        auto res = requestLogin(login);

        EXPECT_EQ(UserRes_Reply_LoginDeny, res);
        handler.clear();
    }

    {
        pb::UserReq_Login login;
        login.mutable_cred()->set_name("USER_NAME");
        login.set_password("bad_pass");

        auto res = requestLogin(login);

        EXPECT_EQ(UserRes_Reply_LoginDeny, res);
        handler.clear();
    }
}


TEST_F(userLoginTest, goodCredentials){
    {
        pb::UserReq_Login login;
        login.mutable_cred()->set_name("USER_NAME");
        login.set_password("secret_pass");

        auto res = requestLogin(login);

        EXPECT_EQ(UserRes_Reply_LoginPass, res);
        handler.clear();
    }

    {
        pb::UserReq_Login login;
        login.mutable_cred()->set_email("EMAIL@asdfg.asdf");
        login.set_password("secret_pass");

        EXPECT_EQ(UserRes_Reply_LoginPass, requestLogin(login));
        handler.clear();
    }
}

TEST_F(userLoginTest, doubleLogin){
    {
        pb::UserReq_Login login;
        login.mutable_cred()->set_name("USER_NAME");
        login.set_password("secret_pass");

        EXPECT_EQ(UserRes_Reply_LoginPass, requestLogin(login));
        EXPECT_EQ(UserRes_Reply_UserOnline, requestLogin(login));
    }
}
