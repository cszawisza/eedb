#include "gtest/gtest.h"

#include "Adapters/Protobuf/AclAdapter.hpp"

TEST( StatTest, defaultValues ){
    ProtobufAclAdapter sut;

    EXPECT_EQ( sut.get_id(), 0 );
    EXPECT_EQ( sut.get_owner(), 0 );
    EXPECT_EQ( sut.get_status(), 0);
}

TEST( ProtobufAclAdapterTests, hasFoo ){
    ProtobufAclAdapter sut;

    EXPECT_FALSE( sut.has_group() );
    EXPECT_FALSE( sut.has_id() );
    EXPECT_FALSE( sut.has_owner() );

    sut.set_id( 1 );
    sut.set_group( 2 );
    sut.set_owner( 3 );

    EXPECT_TRUE ( sut.has_id() );
    EXPECT_TRUE ( sut.has_group() );
    EXPECT_TRUE ( sut.has_owner() );
    EXPECT_FALSE( sut.has_status() );
}

TEST( ProtobufAclAdapterTest, clearField ){
    ProtobufAclAdapter sut;

    EXPECT_FALSE( sut.has_group() );
    sut.set_group(7);
    EXPECT_TRUE( sut.has_group() );
    sut.clear_group();
    EXPECT_FALSE(sut.has_group() );
}
