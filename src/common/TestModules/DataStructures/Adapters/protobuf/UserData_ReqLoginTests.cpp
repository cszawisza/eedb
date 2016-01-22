#include <gmock/gmock.h>

#include <DataStructures/Adapters/Protobuf/CommonDataStructuresAdapter.hpp>
#include <DataStructures/Adapters/Protobuf/UserRequestAdapter.hpp>

class UserDataLoginTests : public testing::Test{
protected:
    requests::user::Login sut;
};

TEST_F(UserDataLoginTests, ctor){
    EXPECT_FALSE(sut.has_password());
    EXPECT_FALSE(sut.has_credentials());
}

TEST_F(UserDataLoginTests, setDataByPointer ){
    sut.password();
    sut.credentials();

    EXPECT_TRUE(sut.has_password());
    EXPECT_TRUE(sut.has_credentials());
}

TEST_F(UserDataLoginTests, setData ){
    sut.set_password("");
    EXPECT_TRUE(sut.has_password());
}
