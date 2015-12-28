#include <gmock/gmock.h>

#include <DataStructures/Adapters/Protobuf/UserRequestAdapter.hpp>

using namespace requests::user;

class UserDataGetTests : public testing::Test{
protected:
    Get sut;
    void all_false()
    {
        EXPECT_FALSE(sut.has_requestedAcl());
        EXPECT_FALSE(sut.has_requestedAddress());
        EXPECT_FALSE(sut.has_requestedAvatar());
        EXPECT_FALSE(sut.has_requestedDescription());
        EXPECT_FALSE(sut.has_requestedPhoneNumber());
        EXPECT_FALSE(sut.has_requestedUid());
    }

    void all_true(){
        EXPECT_TRUE(sut.has_requestedAcl());
        EXPECT_TRUE(sut.has_requestedAddress());
        EXPECT_TRUE(sut.has_requestedAvatar());
        EXPECT_TRUE(sut.has_requestedDescription());
        EXPECT_TRUE(sut.has_requestedPhoneNumber());
        EXPECT_TRUE(sut.has_requestedUid());
    }
};


TEST_F(UserDataGetTests, ctor){
    all_false();
}

TEST_F(UserDataGetTests, setFalseDontChangeData ){
    sut.request_acl(false);
    sut.request_address(false);
    sut.request_avatar(false);
    sut.request_description(false);
    sut.request_phoneNumber(false);
    sut.request_uid(false);

    all_false();
}

TEST_F(UserDataGetTests, setTrue ){
    sut.request_acl();
    sut.request_address();
    sut.request_avatar();
    sut.request_description();
    sut.request_phoneNumber();
    sut.request_uid();

    all_true();
}

TEST_F(UserDataGetTests, clearBySetFalse ){
    sut.request_acl();
    sut.request_address();
    sut.request_avatar();
    sut.request_description();
    sut.request_phoneNumber();
    sut.request_uid();
    all_true();

    sut.request_acl(false);
    sut.request_address(false);
    sut.request_avatar(false);
    sut.request_description(false);
    sut.request_phoneNumber(false);
    sut.request_uid(false);
    all_false();
}


TEST_F(UserDataGetTests, getCriteria ){
    sut.criteria();
}
