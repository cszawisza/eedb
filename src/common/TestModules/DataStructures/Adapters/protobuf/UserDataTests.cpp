#include "gtest/gtest.h"

#include "Interfaces/AclData.hpp"

#include "Adapters/Protobuf/AclAdapter.hpp"
#include "Adapters/Protobuf/UserAdapter.hpp"

TEST( ProtobufUserDataAdapterTest, getAcl ){
    ProtobufUserAddAdapter sut;

    data::IAcl *acl = sut.acl();
    acl->set_owner(7);
    acl->set_id(1);

    EXPECT_EQ( sut.acl()->get_owner(), 7);
    EXPECT_EQ( sut.acl()->get_id(), 1);
}

TEST(ProtobufUserDataAdapterTest, assignAcl ){
    ProtobufUserAddAdapter sut;

    data::IAcl *acl = new ProtobufAclAdapter();
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
