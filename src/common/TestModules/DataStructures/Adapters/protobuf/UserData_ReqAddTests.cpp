#include <gmock/gmock.h>

#include <DataStructures/Adapters/Protobuf/UserRequestAdapter.hpp>
#include <DataStructures/Adapters/Protobuf/AclAdapter.hpp>

using namespace requests::user;

class UserDataAddReqTests : public testing::Test{
protected:
    Add sut;

    void make_roundtrip(){

    }

    void all_true()
    {
        EXPECT_TRUE(sut.has_address());
        EXPECT_TRUE(sut.has_avatar());
        EXPECT_TRUE(sut.has_email());
        EXPECT_TRUE(sut.has_nickname());
        EXPECT_TRUE(sut.has_password());
        EXPECT_TRUE(sut.has_phoneNumber());
        EXPECT_TRUE(sut.has_acl());
    }

    void all_false()
    {
        EXPECT_FALSE(sut.has_acl());
        EXPECT_FALSE(sut.has_address());
        EXPECT_FALSE(sut.has_avatar());
        EXPECT_FALSE(sut.has_email());
        EXPECT_FALSE(sut.has_id());
        EXPECT_FALSE(sut.has_nickname());
        EXPECT_FALSE(sut.has_password());
        EXPECT_FALSE(sut.has_phoneNumber());
    }
};

TEST_F(UserDataAddReqTests, ctor){
    all_false();
}

TEST_F(UserDataAddReqTests, setDataByPointer ){
    sut.acl();
    sut.address();
    sut.avatar();
    sut.email();
    sut.nickname();
    sut.password();
    sut.phoneNumber();

    all_true();
}


TEST_F(UserDataAddReqTests, setDataBySetAccesor ){
    sut.assign_acl( new ProtobufAclAdapter() );

    sut.set_address("adr");
    sut.set_avatar("avatardata");
    sut.set_email("email123@ww.ww");
    sut.set_nickname("nickname");
    sut.set_password("pass");
    sut.set_phoneNumber("number123");

    all_true();
}

TEST_F(UserDataAddReqTests, clearData ){
    sut.assign_acl( new ProtobufAclAdapter() );
    sut.set_address("adr");
    sut.set_avatar("avatardata");
    sut.set_email("email123@ww.ww");
    sut.set_nickname("nickname");
    sut.set_password("pass");
    sut.set_phoneNumber("number123");

    sut.clear_acl();
    sut.clear_address();
    sut.clear_avatar();
    sut.clear_description();
    sut.clear_email();
    sut.clear_id();
    sut.clear_nickname();
    sut.clear_password();
    sut.clear_phoneNumber();

    all_false();
}
