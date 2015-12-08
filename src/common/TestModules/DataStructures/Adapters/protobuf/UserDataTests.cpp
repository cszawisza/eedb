#include "gtest/gtest.h"

#include "Interfaces/AclData.hpp"

#include "Adapters/Protobuf/AclAdapter.hpp"
#include "Adapters/Protobuf/UserAdapter.hpp"

TEST( ProtobufUserDataAdapterTest, getAcl ){
    ProtobufUserAddAdapter sut;

    auto acl = sut.acl();
    acl->set_owner(7);
    acl->set_id(1);

    EXPECT_EQ( sut.acl()->get_owner(), 7);
    EXPECT_EQ( sut.acl()->get_id(), 1);
}

TEST(ProtobufUserDataAdapterTest, assignAcl ){
    ProtobufUserAddAdapter sut;

    auto acl = std::make_shared<ProtobufAclAdapter>();
    acl->set_owner(7);
    acl->set_id(1);
    sut.assign_acl(acl); // move ovnership to adapter

    EXPECT_EQ( sut.acl()->get_owner(), 7);
    EXPECT_EQ( sut.acl()->get_id(), 1);
}

TEST(ProtobufUserAddAdapterTest, hasFOO ){
    ProtobufUserAddAdapter sut;
    EXPECT_FALSE(sut.has_acl());

    sut.acl();
    EXPECT_TRUE( sut.has_acl() );

    sut.clear_acl();
    sut.acl();

    EXPECT_TRUE( sut.has_acl() );
}

TEST(ProtobufUserAdapterTest, assign ){
    ProtobufUserAdapter sut;

    EXPECT_FALSE( sut.has_add() );
    EXPECT_FALSE( sut.has_login() );

    sut.assign( std::make_shared<ProtobufUserAddAdapter>() );
    EXPECT_TRUE ( sut.has_add() );
    EXPECT_FALSE( sut.has_login() );

    sut.assign( std::make_shared<ProtobufUserLoginAdapter>() );
    EXPECT_TRUE ( sut.has_login() );
    EXPECT_FALSE( sut.has_add() );
}

TEST(ProtobufUserAdapterTest, getPointerTest ){
    ProtobufUserAdapter sut;

    EXPECT_FALSE( sut.has_add() );
    EXPECT_FALSE( sut.has_login() );

    sut.add();
    EXPECT_TRUE ( sut.has_add() );
    EXPECT_FALSE( sut.has_login() );

    sut.login();
    EXPECT_TRUE ( sut.has_login() );
    EXPECT_FALSE( sut.has_add() );
}
