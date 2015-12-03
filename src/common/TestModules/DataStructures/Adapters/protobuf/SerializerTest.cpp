#include "gtest/gtest.h"

#include <QByteArray>
#include "DataStructures/Interfaces/UserData.hpp"
#include "DataStructures/Adapters/Protobuf/UserAdapter.hpp"
#include "DataStructures/Adapters/Protobuf/ClientRequestAdapter.hpp"
#include "DataStructures/Adapters/Protobuf/RequestsSerializer.hpp"

class ProtobufSerializerTest : public testing::Test {
public:
    ProtobufSerializerTest()
    {}
protected:
    ProtobufRequestsSerializer sut;
    ProtobufClientRequestsAdapter m_data;
};


TEST_F( ProtobufSerializerTest, ctor ){
    data::requests::user::IAdd *addAdp =  new ProtobufUserAddAdapter();
    addAdp->set_nickname("asdf");
    addAdp->set_password("asdfg");
    addAdp->set_email("cycki@xy.xy");

    data::requests::IUser *usrAdp = new ProtobufUserAdapter();
    usrAdp->assign(addAdp);

    data::IClientRequest *req = m_data.newClientRequest();
    req->assign_user( usrAdp );

    auto array = sut.serializeToByteArray( &m_data );
    EXPECT_GT(array.size(), 0);
    EXPECT_TRUE(array.contains("cycki@xy.xy"));
}
