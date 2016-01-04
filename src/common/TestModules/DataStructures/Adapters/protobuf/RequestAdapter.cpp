#include "gtest/gtest.h"

#include "DataStructures/Adapters/Protobuf/UserRequestAdapter.hpp"
#include "DataStructures/Adapters/Protobuf/CategoryRequestAdapter.hpp"

#include "DataStructures/Adapters/Protobuf/ClientRequestAdapter.hpp"


class ProtobufClientRequestAdapterTest : public testing::Test {
public:
    ProtobufClientRequestAdapterTest()
    {}
protected:
    ClientRequest sut;
};

TEST_F(ProtobufClientRequestAdapterTest, ctor ){
    EXPECT_FALSE(sut.has_user());
    EXPECT_FALSE(sut.has_category());
}

//TEST_F(ProtobufClientRequestAdapterTest, assign_user){
//    EXPECT_FALSE(sut.has_user());
//    auto msg = new requests::User();
//    sut.assign(msg);
//    EXPECT_TRUE(sut.has_user());

//    sut.clear_user();

//    EXPECT_FALSE(sut.has_user());
//    sut.user();
//    EXPECT_TRUE(sut.has_user());
//}

//TEST_F(ProtobufClientRequestAdapterTest, assign_category){
//    EXPECT_FALSE(sut.has_category());
//    auto msg = new requests::Category();
//    sut.assign(msg);
//    EXPECT_TRUE(sut.has_category());

//    sut.clear_category();

//    EXPECT_FALSE(sut.has_category());
//    sut.user();
//    EXPECT_TRUE(sut.has_category());
//}

TEST_F(ProtobufClientRequestAdapterTest, getReturnsDefault){
    EXPECT_FALSE(sut.has_user());
    EXPECT_FALSE(sut.get_user().has_add());
    EXPECT_FALSE(sut.get_user().has_get());
    EXPECT_FALSE(sut.get_user().has_login());
}