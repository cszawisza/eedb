#include "gtest/gtest.h"

#include "Interfaces/AclData.hpp"

#include "Adapters/Protobuf/AclAdapter.hpp"
#include "Adapters/Protobuf/UserRequestAdapter.hpp"

#include "user.pb.h"

using namespace requests;
using namespace requests::user;

TEST(ProtobufUserAdapterTest, assignOneOf ){
    User sut;

    EXPECT_FALSE( sut.has_add() );
    EXPECT_FALSE( sut.has_login() );
    EXPECT_FALSE( sut.has_get() );

//    sut.assign( new Add() );
//    EXPECT_TRUE ( sut.has_add() );
//    EXPECT_FALSE( sut.has_login() );
//    EXPECT_FALSE( sut.has_get() );

//    sut.assign( new Login() );
//    EXPECT_FALSE( sut.has_add() );
//    EXPECT_TRUE ( sut.has_login() );
//    EXPECT_FALSE( sut.has_get() );

//    sut.assign( new Get() );
//    EXPECT_FALSE( sut.has_add() );
//    EXPECT_FALSE( sut.has_login() );
//    EXPECT_TRUE ( sut.has_get() );
}

TEST(ProtobufUserAdapterTest, getPointerTest ){
    User sut = User(  );

    EXPECT_FALSE( sut.has_add() );
    EXPECT_FALSE( sut.has_login() );
    EXPECT_FALSE( sut.has_get() );

    sut.add();
    EXPECT_TRUE ( sut.has_add() );
    EXPECT_FALSE( sut.has_login() );
    EXPECT_FALSE( sut.has_get() );

    sut.login();
    EXPECT_FALSE( sut.has_add() );
    EXPECT_TRUE ( sut.has_login() );
    EXPECT_FALSE( sut.has_get() );

    sut.get();
    EXPECT_FALSE( sut.has_add() );
    EXPECT_FALSE( sut.has_login() );
    EXPECT_TRUE ( sut.has_get() );
}

TEST(ProtobufUserAdapterTest, getMessageMethods ){
    User sut = User(  );

    sut.add()->set_address("adr");
    sut.add()->set_email("email");

    EXPECT_EQ( sut.get_add().get_address(), "adr" );
    EXPECT_EQ( sut.get_add().get_email(), "email" );
    sut.clear_add();

    sut.get()->request_acl();
    sut.get()->request_avatar();
    EXPECT_TRUE( sut.get_get().has_requestedAcl() );
    EXPECT_TRUE( sut.get_get().has_requestedAvatar());
    sut.clear_get();

    sut.login()->set_password("pass");
    sut.login()->credentials()->set_authorization("my_nickname");
    EXPECT_EQ( sut.get_login().get_password(), "pass");
    EXPECT_EQ( sut.get_login().get_credentials().is_authorized_by_nickname(), true);
}
