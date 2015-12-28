#include "gtest/gtest.h"

#include <QByteArray>
#include "DataStructures/Interfaces/UserRequests.hpp"
#include "DataStructures/Adapters/Protobuf/ServerResponseAdapter.hpp"
#include "DataStructures/Adapters/Protobuf/UserRequestAdapter.hpp"
#include "DataStructures/Adapters/Protobuf/ClientRequestAdapter.hpp"
#include "DataStructures/Adapters/Protobuf/RequestSerializer.hpp"
#include "DataStructures/Adapters/Protobuf/ResponsesSerializer.hpp"

class ProtobufSerializerTest : public testing::Test {
public:
    ProtobufSerializerTest()
    {}
protected:
    RequestsSerializer sut;
    ClientRequest m_data;
};

void set_data(requests::user::IAdd* add)
{
    add->set_nickname("asdf");
    add->set_password("asdfg");
    add->set_email("cycki@xy.xy");
    add->set_address("my address");
    add->set_avatar("ajdshajhsdadsjkfkjhgsadgfjhasd");
    add->set_phoneNumber("asd12344");
    add->set_description("alskdalksdjlkalkjsdjalkjsklkjlkjlkjlkjlkjlkjlkjlkjlkj");
}

TEST_F( ProtobufSerializerTest, ctor ){
    auto addAdp =  new requests::user::Add();
    addAdp->set_nickname("asdf");
    addAdp->set_password("asdfg");
    addAdp->set_email("cycki@xy.xy");

    auto usrAdp = new requests::User();
    usrAdp->assign(addAdp);

    m_data.assign_user(usrAdp);

    auto array = sut.serializeClientRequest( &m_data );
    EXPECT_GT(array.size(), 0);
    EXPECT_TRUE(array.contains("cycki@xy.xy"));
}

TEST_F( ProtobufSerializerTest, goUp ){
    auto addAdp = m_data.user()->add();

    set_data(addAdp);

    auto array = sut.serializeClientRequest( &m_data );

    EXPECT_GT(array.size(), 0);
    EXPECT_TRUE(array.contains("cycki@xy.xy"));
    EXPECT_TRUE(array.contains("ajdshajhsdadsjkfkjhgsadgfjhasd"));
    EXPECT_TRUE(array.contains("alskdalksdjlkalkjsdjalkjsklkjlkjlkjlkjlkjlkjlkjlkjlkj"));
    EXPECT_TRUE(array.contains("asd12344"));
}

class ProtobufDeserializerTest : public testing::Test {
public:
    ProtobufDeserializerTest()
    {}
protected:
    ResponseSerializer res_sut;

    RequestsSerializer sut;
    ClientRequest m_data;
};

TEST_F( ProtobufDeserializerTest, goUp ){
    auto add = m_data.user()->add();

    set_data(add);

    auto req = res_sut.parseClientRequest(sut.serializeClientRequest(&m_data));

    ASSERT_TRUE(req->has_user());
    auto addReq = req->user()->add();

    EXPECT_EQ(add->get_nickname(),      addReq->get_nickname());
    EXPECT_EQ(add->get_password(),      addReq->get_password());
    EXPECT_EQ(add->get_email(),         addReq->get_email());
    EXPECT_EQ(add->get_avatar(),        addReq->get_avatar());
    EXPECT_EQ(add->get_phoneNumber(),   addReq->get_phoneNumber());
    EXPECT_EQ(add->get_description(),   addReq->get_description());
}

TEST_F( ProtobufDeserializerTest, reuseMessages ){
    auto add = m_data.user()->add();
    auto req = new ClientRequest();
    auto dat = QByteArray();

    set_data(add);

    sut.serializeClientRequest(&m_data, dat );
    res_sut.parseClientRequest(dat, req);

    ASSERT_TRUE(req->has_user());
    auto addReq = req->user()->add();

    EXPECT_EQ(add->get_nickname(),      addReq->get_nickname());
    EXPECT_EQ(add->get_password(),      addReq->get_password());
    EXPECT_EQ(add->get_email(),         addReq->get_email());
    EXPECT_EQ(add->get_avatar(),        addReq->get_avatar());
    EXPECT_EQ(add->get_phoneNumber(),   addReq->get_phoneNumber());
    EXPECT_EQ(add->get_description(),   addReq->get_description());

    delete req;
}
