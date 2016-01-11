#include "gtest/gtest.h"
#include "TestCommon.hpp"

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
        add.set_email("EMAIL@asdfg.asdf");
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
        handler.process(db, &req);

//        return handler.getLastResponse().userres().code(0);
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

//        EXPECT_EQ(UserRes_Reply_UserDontExist, res);
//        handler.clear();
    }

//    {
//        protobuf::UserReq_Login login;
//        login.mutable_cred()->set_email("BAD_EMAIL");
//        login.set_password("secret_pass");

//        auto res = requestLogin(login);

//        EXPECT_EQ(UserRes_Reply_UserDontExist, res);
//        handler.clear();
//    }

//    {
//        protobuf::UserReq_Login login;
//        login.mutable_cred()->set_email("aaa' OR TRUE -- "); // simple sql injection
//        login.set_password("aaa\\' OR TRUE -- ");

//        auto res = requestLogin(login);

//        EXPECT_EQ(UserRes_Reply_UserDontExist, res);
//        handler.clear();
//    }

//    {
//        protobuf::UserReq_Login login;
//        login.mutable_cred()->set_email("EMAIL@asdfg.asdf");
//        login.set_password("bad_pass");

//        auto res = requestLogin(login);

//        EXPECT_EQ(UserRes_Reply_LoginDeny, res);
//        handler.clear();
//    }

//    {
//        protobuf::UserReq_Login login;
//        login.mutable_cred()->set_nickname("USER_NAME");
//        login.set_password("bad_pass");

//        auto res = requestLogin(login);

//        EXPECT_EQ(UserRes_Reply_LoginDeny, res);
//        handler.clear();
//    }
}


//TEST_F(userLoginTest, goodCredentials){
//    {
//        protobuf::UserReq_Login login;
//        login.mutable_cred()->set_nickname("USER_NAME");
//        login.set_password("secret_pass");

//        auto res = requestLogin(login);

//        EXPECT_EQ(UserRes_Reply_LoginPass, res);
//        handler.clear();
//    }

//    {
//        protobuf::UserReq_Login login;
//        login.mutable_cred()->set_email("EMAIL@asdfg.asdf");
//        login.set_password("secret_pass");

//        EXPECT_EQ(UserRes_Reply_LoginPass, requestLogin(login));
//        handler.clear();
//    }
//}

//TEST_F(userLoginTest, doubleLogin){
//    {
//        protobuf::UserReq_Login login;
//        login.mutable_cred()->set_nickname("USER_NAME");
//        login.set_password("secret_pass");

//        EXPECT_EQ(UserRes_Reply_LoginPass, requestLogin(login));
//        EXPECT_EQ(UserRes_Reply_UserOnline, requestLogin(login));
//    }
//}
