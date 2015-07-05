#include "gtest/gtest.h"

#include <sqlpp11/sqlpp11.h>
#include "core/user.h"
#include <core/idatabase.h>
#include <memory>

#include "../../common.h"

#include "sql_schema/t_users.h"
#include "sql_schema/t_user_history.h"

class userLoginTest : public ::testing::Test
{
public:
   userLoginTest() {
       schema::t_users u;
       createBackup(u);

       pb::MsgUserRequest_Add add;
       add.mutable_basic()->set_name("USER_NAME");
       add.mutable_basic()->set_email("EMAIL@asdfg.asdf");
       add.set_password("secret_pass");

       requestAdd(add);
   }

   ~userLoginTest(){
       schema::t_users u;
       restoreBackup(u);
   }

   const ResponseCode &requestAdd( pb::MsgUserRequest_Add &msg){
       pb::ClientRequest req;

       auto userReq = req.mutable_msguserreq();
       userReq->mutable_add()->CopyFrom(msg);

       handler.process(req);

       return handler.getLastResponse().codes(0);
   }

   const ResponseCode &requestLogin( pb::MsgUserRequest_Login &msg){
       pb::ClientRequest req;

       auto userReq = req.mutable_msguserreq();
       userReq->mutable_login()->CopyFrom(msg);

       handler.process(req);

       return handler.getLastResponse().codes(0);
   }

   eedb::handlers::User handler;
};


TEST_F(userLoginTest, badCredentials){
    {
        pb::MsgUserRequest_Login login;
        login.mutable_cred()->set_name("BAD_NAME");
        login.set_password("secret_pass");

        auto res = requestLogin(login);

        EXPECT_TRUE(res.error());
        handler.clear();
    }

    {
        pb::MsgUserRequest_Login login;
        login.mutable_cred()->set_email("BAD_EMAIL");
        login.set_password("secret_pass");

        auto res = requestLogin(login);

        EXPECT_TRUE(res.error());
        handler.clear();
    }

    {
        pb::MsgUserRequest_Login login;
        login.mutable_cred()->set_email("aaa' OR TRUE -- "); // simple sql injection
        login.set_password("aaa\\' OR TRUE -- ");

        auto res = requestLogin(login);

        EXPECT_TRUE(res.error());
        handler.clear();
    }

    {
        pb::MsgUserRequest_Login login;
        login.mutable_cred()->set_email("EMAIL@asdfg.asdf");
        login.set_password("bad_pass");

        auto res = requestLogin(login);

        EXPECT_TRUE(res.error());
        handler.clear();
    }

    {
        pb::MsgUserRequest_Login login;
        login.mutable_cred()->set_name("USER_NAME");
        login.set_password("bad_pass");

        auto res = requestLogin(login);

        EXPECT_TRUE(res.error());
        handler.clear();
    }
}


TEST_F(userLoginTest, goodCredentials){
    {
        pb::MsgUserRequest_Login login;
        login.mutable_cred()->set_name("USER_NAME");
        login.set_password("secret_pass");

        auto res = requestLogin(login);

        EXPECT_FALSE(res.error());
        handler.clear();
    }

    {
        pb::MsgUserRequest_Login login;
        login.mutable_cred()->set_email("EMAIL@asdfg.asdf");
        login.set_password("secret_pass");

        auto res = requestLogin(login);

        EXPECT_FALSE(res.error());
        handler.clear();
    }
}

TEST_F(userLoginTest, doubleLogin){
    {
        pb::MsgUserRequest_Login login;
        login.mutable_cred()->set_name("USER_NAME");
        login.set_password("secret_pass");

        auto res = requestLogin(login);

        EXPECT_FALSE(res.error());
        res.Clear();
        res = requestLogin(login);
        EXPECT_TRUE(res.error());
    }
}
