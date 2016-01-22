#include "gtest/gtest.h"

#include "DataStructures/Adapters/Protobuf/CommonDataStructuresAdapter.hpp"

class AuthorizationDataTests : public testing::Test{
protected:
    ProtobufAuthorizationDataAdapter sut;
};

TEST_F(AuthorizationDataTests, canTakeIntAndStringData ){
    sut.set_authorization("my_nickname");
    sut.set_authorization(123);
}

TEST_F(AuthorizationDataTests, stringOverloadCanTakeAmailOrNickname ){
    sut.set_authorization("my_nickname");
    EXPECT_TRUE( sut.is_authorized_by_nickname() );
    EXPECT_FALSE(sut.is_authorized_by_email() );
    EXPECT_FALSE(sut.is_authorized_by_id() );
}

TEST_F(AuthorizationDataTests, authorizeByEmail ){
    sut.set_authorization("email@email.com");
    EXPECT_FALSE( sut.is_authorized_by_nickname() );
    EXPECT_TRUE(sut.is_authorized_by_email() );
    EXPECT_FALSE(sut.is_authorized_by_id() );
}

TEST_F(AuthorizationDataTests, authorizeByID ){
    sut.set_authorization( 4 );
    EXPECT_FALSE( sut.is_authorized_by_nickname() );
    EXPECT_FALSE(sut.is_authorized_by_email() );
    EXPECT_TRUE(sut.is_authorized_by_id() );
}
