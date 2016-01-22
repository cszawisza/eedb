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

    EXPECT_FALSE( sut.has_groups() );
    EXPECT_FALSE( sut.has_id() );
    EXPECT_FALSE( sut.has_owner() );

    sut.set_id( 1 );
    sut.set_groups( 2 );
    sut.set_owner( 3 );

    EXPECT_TRUE ( sut.has_id() );
    EXPECT_TRUE ( sut.has_groups() );
    EXPECT_TRUE ( sut.has_owner() );
    EXPECT_FALSE( sut.has_status() );
}

TEST( ProtobufAclAdapterTest, clearField ){
    ProtobufAclAdapter sut;

    EXPECT_FALSE( sut.has_groups() );
    sut.set_groups(7);
    EXPECT_TRUE( sut.has_groups() );
    sut.clear_groups();
    EXPECT_FALSE(sut.has_groups() );
}
