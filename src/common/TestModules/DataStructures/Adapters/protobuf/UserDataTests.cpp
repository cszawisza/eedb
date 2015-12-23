#include "gtest/gtest.h"

#include "Interfaces/AclData.hpp"

#include "Adapters/Protobuf/AclAdapter.hpp"
#include "Adapters/Protobuf/UserAdapter.hpp"

#include "user.pb.h"

using namespace requests;
using namespace requests::user;

TEST( ProtobufUserDataAdapterTest, getAcl ){
    ProtobufUserAddAdapter sut;

    auto acl = sut.acl();
    acl->set_owner(7);
    acl->set_id(1);

    EXPECT_EQ( sut.get_acl().get_owner(), 7);
    EXPECT_EQ( sut.get_acl().get_id(), 1);
}

TEST( ProtobufUserDataAdapterTest, aclAfterClear ){
    ProtobufUserAddAdapter sut;

    auto acl = sut.acl();
    acl->set_owner(7);
    acl->set_id(1);

    sut.clear_acl();

    EXPECT_FALSE(acl->has_owner());
    EXPECT_FALSE(acl->has_id());
}


TEST( ProtobufUserDataAdapterTest, getDefaultAclWhenNoAcl ){
    ProtobufUserAddAdapter sut;
    EXPECT_FALSE(sut.has_acl() );

    EXPECT_FALSE(sut.get_acl().has_groups() );
    EXPECT_FALSE(sut.get_acl().has_id() );
}

TEST(ProtobufUserDataAdapterTest, assignAcl ){
    ProtobufUserAddAdapter sut;

    auto acl = new ProtobufAclAdapter();
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

TEST(ProtobufUserAdapterTest, assignOneOf ){
    ProtobufUserAdapter sut;

    EXPECT_FALSE( sut.has_add() );
    EXPECT_FALSE( sut.has_login() );
    EXPECT_FALSE( sut.has_get() );

    sut.assign( new ProtobufUserAddAdapter() );
    EXPECT_TRUE ( sut.has_add() );
    EXPECT_FALSE( sut.has_login() );
    EXPECT_FALSE( sut.has_get() );

    sut.assign( new ProtobufUserLoginAdapter() );
    EXPECT_FALSE( sut.has_add() );
    EXPECT_TRUE ( sut.has_login() );
    EXPECT_FALSE( sut.has_get() );

    sut.assign( new ProtobufUserGetAdapter() );
    EXPECT_FALSE( sut.has_add() );
    EXPECT_FALSE( sut.has_login() );
    EXPECT_TRUE ( sut.has_get() );
}

TEST(ProtobufUserAdapterTest, getPointerTest ){
    ProtobufUserAdapter sut = ProtobufUserAdapter(  );

    EXPECT_FALSE( sut.has_add() );
    EXPECT_FALSE( sut.has_login() );
    EXPECT_FALSE( sut.has_get() );


    sut.add();
    EXPECT_TRUE ( sut.has_add() );
    EXPECT_FALSE( sut.has_login() );
    EXPECT_FALSE( sut.has_get() );

    sut.login();
    EXPECT_FALSE( sut.has_add() );
    EXPECT_TRUE ( sut.has_login() );
    EXPECT_FALSE( sut.has_get() );

    sut.get();
    EXPECT_FALSE( sut.has_add() );
    EXPECT_FALSE( sut.has_login() );
    EXPECT_TRUE ( sut.has_get() );
}
