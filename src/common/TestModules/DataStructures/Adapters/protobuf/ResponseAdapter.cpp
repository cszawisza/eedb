#include "gtest/gtest.h"

#include "DataStructures/Adapters/Protobuf/UserResponseAdapter.hpp"
#include "DataStructures/Adapters/Protobuf/ServerResponseAdapter.hpp"


class ProtobufServerResponseAdapterTest : public testing::Test {
public:
    ProtobufServerResponseAdapterTest()
    {}
protected:
    ServerResponse sut;
};

TEST_F(ProtobufServerResponseAdapterTest, ctor ){
    EXPECT_FALSE(sut.has_user());
}

TEST_F(ProtobufServerResponseAdapterTest, assign){
    EXPECT_FALSE(sut.has_user());

    auto usrRes = new responses::User();
//    auto catres = new responses::ProtobufCategoryAdapter();

    sut.assign(usrRes);
    EXPECT_TRUE(sut.has_user());

    sut.clear_user();

    EXPECT_FALSE(sut.has_user());
    sut.user();
    EXPECT_TRUE(sut.has_user());
}

//TEST_F(ProtobufServerResponseAdapterTest, getReturnsDefault){
//    EXPECT_FALSE(sut.has_user());
//}
