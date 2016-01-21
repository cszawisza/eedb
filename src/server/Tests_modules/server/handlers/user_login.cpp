#include "gtest/gtest.h"
#include "TestCommon.hpp"

#include "database/idatabase.h"
#include "ProcessingUnits/UserPU.hpp"

#include "DataStructures/Adapters/Protobuf/ClientRequestAdapter.hpp"
#include "DataStructures/Adapters/Protobuf/ServerResponseAdapter.hpp"

#include "DataStructures/Adapters/Protobuf/UserRequestAdapter.hpp"
#include "DataStructures/Adapters/Protobuf/UserResponseAdapter.hpp"

using namespace test;

class userLoginTest : public ::testing::Test
{
public:
    userLoginTest():
        login( req.user()->login() )
    {
        db.start_transaction();

        ///TODO create a std implementation
        auto add = requests::user::Add();
        add.set_nickname("USER_NAME");
        add.set_email("email@asdfg.asdf");
        add.set_password("secret_pass");

        requestAdd(add);
    }

    ~userLoginTest(){
        db.rollback_transaction(false);
    }

    void requestAdd( requests::user::IAdd &msg){
        ClientRequest userReq;

//        auto userReq = req.mutable_userreq();
//        userReq->mutable_add()->CopyFrom(msg);
        auto a = userReq.user()->add();
        a->set_nickname( msg.get_nickname() );
        a->set_email( msg.get_email() );
        a->set_password( msg.get_password() );

        handler.process(db, &userReq);

//        return handler.getLastResponse().userres().code(0);
    }

    responses::user::ILogin::LoginErrors requestLogin(){
        handler.setOutputData(std::make_shared<ServerResponse>());
        handler.process(db, &req);

        return handler.response()->user()->login()->get_error_code();
    }
    DB db;
    eedb::pu::UserPU handler;
    ClientRequest req;
    requests::user::ILogin *login;
};


TEST_F(userLoginTest, badCredentials){
    {
        login->credentials()->set_authorization("BAD_NAME");
        login->set_password("secret_pass");

        auto res = requestLogin();

        EXPECT_EQ( responses::user::Login::Error_UserDontExists, res);
        handler.clear();
    }

    {
        login->credentials()->set_authorization("BAD_EMAIL@bad_domain.com");

        auto res = requestLogin();

        EXPECT_EQ(responses::user::Login::Error_UserDontExists, res);
        handler.clear();
    }

    {
        login->credentials()->set_authorization("aaa' OR TRUE -- "); // simple sql injection
        login->set_password("aaa\\' OR TRUE -- ");

        auto res = requestLogin();

        EXPECT_EQ(responses::user::Login::Error_UserDontExists, res);
        handler.clear();
    }

    {
        login->credentials()->set_authorization("email@asdfg.asdf");
        login->set_password("bad_pass");

        auto res = requestLogin();

        EXPECT_EQ(responses::user::Login::Error_WrongNameOrPass, res);
        handler.clear();
    }

    {
        login->credentials()->set_authorization("USER_NAME");
        login->set_password("bad_pass");

        auto res = requestLogin();

        EXPECT_EQ(responses::user::Login::Error_WrongNameOrPass, res);
        handler.clear();
    }
}

TEST_F(userLoginTest, goodCredentialsTest1)
{
    login->credentials()->set_authorization("USER_NAME");
    login->set_password("secret_pass");

    EXPECT_EQ(responses::user::ILogin::noError, requestLogin());
}

TEST_F(userLoginTest, goodCredentialsTest2)
{
    login->credentials()->set_authorization("email@asdfg.asdf");
    login->set_password("secret_pass");

    EXPECT_EQ(responses::user::ILogin::noError, requestLogin());
}

TEST_F(userLoginTest, doubleLogin){
    login->credentials()->set_authorization("email@asdfg.asdf");
    login->set_password("secret_pass");

    EXPECT_EQ(responses::user::ILogin::noError, requestLogin());
    EXPECT_EQ(responses::user::ILogin::Error_UserOnline, requestLogin());
}
