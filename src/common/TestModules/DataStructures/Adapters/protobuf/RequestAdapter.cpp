#include "gtest/gtest.h"

#include "DataStructures/Adapters/Protobuf/UserRequestAdapter.hpp"
#include "DataStructures/Adapters/Protobuf/CategoryRequestAdapter.hpp"

#include "DataStructures/Adapters/Protobuf/ClientRequestAdapter.hpp"
#include "Interfaces/DefinedActions.hpp"

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

TEST_F(ProtobufClientRequestAdapterTest, getActionType){
    EXPECT_FALSE(sut.message_type().is_initialized());

    sut.category();
    EXPECT_EQ( sut.message_type(), actions::typeCategory);

    sut.user();
    EXPECT_EQ( sut.message_type(), actions::typeUser);
}
