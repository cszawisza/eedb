#include "gtest/gtest.h"

#include <QByteArray>
#include "DataStructures/Interfaces/UserData.hpp"
#include "DataStructures/Adapters/Protobuf/UserAdapter.hpp"
#include "DataStructures/Adapters/Protobuf/ClientRequestAdapter.hpp"
#include "DataStructures/Adapters/Protobuf/RequestsSerializer.hpp"
#include "DataStructures/Adapters/Protobuf/RequestsDeserializer.hpp"

class ProtobufSerializerTest : public testing::Test {
public:
    ProtobufSerializerTest()
    {}
protected:
    ProtobufRequestsSerializer sut;
    ProtobufClientRequestAdapter m_data;
};


//TEST_F( ProtobufSerializerTest, ctor ){
//    auto addAdp =  new ProtobufUserAddAdapter();
//    addAdp->set_nickname("asdf");
//    addAdp->set_password("asdfg");
//    addAdp->set_email("cycki@xy.xy");

//    data::requests::IUser *usrAdp = new ProtobufUserAdapter();
//    usrAdp->assign(addAdp);

//    m_data.assign_user(usrAdp);
////    auto req = m_data.newClientRequest();
////    req->assign_user( usrAdp );

//    auto array = sut.serializeToByteArray( &m_data );
//    EXPECT_GT(array.size(), 0);
//    EXPECT_TRUE(array.contains("cycki@xy.xy"));
//}

TEST_F( ProtobufSerializerTest, goUp ){
    auto addAdp = m_data.user()->add();

    addAdp->set_nickname("asdf");
    addAdp->set_password("asdfg");
    addAdp->set_email("cycki@xy.xy");
    addAdp->set_address("my address");
    addAdp->set_avatar("ajdshajhsdadsjkfkjhgsadgfjhasd");
    addAdp->set_phoneNumber("asd12344");
    addAdp->set_description("alskdalksdjlkalkjsdjalkjsklkjlkjlkjlkjlkjlkjlkjlkjlkj");

    auto array = sut.serializeToByteArray( &m_data );

    EXPECT_GT(array.size(), 0);
    EXPECT_TRUE(array.contains("cycki@xy.xy"));
}

class ProtobufDeserializerTest : public testing::Test {
public:
    ProtobufDeserializerTest()
    {}
protected:
    ProtobufRequestsSerializer serializer;
    ProtobufRequestsDeserializer sut;
    ProtobufClientRequestAdapter m_data;
};

TEST_F( ProtobufDeserializerTest, goUp ){
    auto add = m_data.user()->add();

    add->set_nickname("asdf");
    add->set_password("asdfg");
    add->set_email("cycki@xy.xy");
    add->set_address("my address");
    add->set_avatar("ajdshajhsdadsjkfkjhgsadgfjhasd");
    add->set_phoneNumber("asd12344");
    add->set_description("alskdalksdjlkalkjsdjalkjsklkjlkjlkjlkjlkjlkjlkjlkjlkj");

    auto req = sut.parseFromByteArray(serializer.serializeToByteArray( &m_data ));

    ASSERT_TRUE(req->has_user());
    auto addReq = req->user()->add();

    EXPECT_EQ(add->get_nickname(), addReq->get_nickname());
    EXPECT_EQ(add->get_password(), addReq->get_password());
    EXPECT_EQ(add->get_email(), addReq->get_email());
    EXPECT_EQ(add->get_avatar(), addReq->get_avatar());
    EXPECT_EQ(add->get_phoneNumber(), addReq->get_phoneNumber());
    EXPECT_EQ(add->get_description(), addReq->get_description());
}
