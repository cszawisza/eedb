#include "gtest/gtest.h"

#include "DataStructures/Adapters/Protobuf/UserResponseAdapter.hpp"
#include "DataStructures/Adapters/Protobuf/CategoryResponseAdapter.hpp"

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
    EXPECT_FALSE(sut.has_category());
}

TEST_F(ProtobufServerResponseAdapterTest, userres){
    sut.user()->add();
    EXPECT_TRUE( sut.has_user() );

    EXPECT_TRUE( sut.get_user().has_add() );
    EXPECT_FALSE( sut.get_user().has_get() );
    EXPECT_FALSE( sut.get_user().has_login() );

    sut.user()->get();
    EXPECT_FALSE( sut.get_user().has_add() );
    EXPECT_TRUE( sut.get_user().has_get() );
    EXPECT_FALSE( sut.get_user().has_login() );

    sut.user()->login();
    EXPECT_FALSE( sut.get_user().has_add() );
    EXPECT_FALSE( sut.get_user().has_get() );
    EXPECT_TRUE( sut.get_user().has_login() );
}

TEST_F(ProtobufServerResponseAdapterTest, categoryres){
    sut.category()->add();
    EXPECT_TRUE( sut.has_category() );

    EXPECT_TRUE( sut.get_category().has_add() );
    EXPECT_FALSE( sut.get_category().has_get() );

    sut.category()->get();
    EXPECT_FALSE( sut.get_category().has_add() );
    EXPECT_TRUE( sut.get_category().has_get() );
}
