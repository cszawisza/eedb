#include "gtest/gtest.h"

#include <QByteArray>
#include <memory>

#include "DataStructures/Interfaces/UserRequests.hpp"
#include "DataStructures/Adapters/Protobuf/ServerResponseAdapter.hpp"
#include "DataStructures/Adapters/Protobuf/UserRequestAdapter.hpp"
#include "DataStructures/Adapters/Protobuf/ClientRequestAdapter.hpp"

class ProtobufSerializerTest : public testing::Test {
public:
    ProtobufSerializerTest()
    {}
protected:
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

    auto array = m_data.serialize();
    EXPECT_GT(array.size(), 0);
    EXPECT_TRUE(array.contains("cycki@xy.xy"));
}

TEST_F( ProtobufSerializerTest, goUp ){
    auto addAdp = m_data.user()->add();

    set_data(addAdp);

    auto array = m_data.serialize();

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
    ClientRequest m_data;
};

TEST_F( ProtobufDeserializerTest, goUp ){
    auto add = m_data.user()->add();

    set_data(add);

    auto req = std::make_shared<ClientRequest>();
    req->parse(m_data.serialize());

    ASSERT_TRUE(req->has_user());
    auto addReq = req->user()->add();

    EXPECT_EQ(add->get_nickname(),      addReq->get_nickname());
    EXPECT_EQ(add->get_password(),      addReq->get_password());
    EXPECT_EQ(add->get_email(),         addReq->get_email());
    EXPECT_EQ(add->get_avatar(),        addReq->get_avatar());
    EXPECT_EQ(add->get_phoneNumber(),   addReq->get_phoneNumber());
    EXPECT_EQ(add->get_description(),   addReq->get_description());
}

//TEST_F( ProtobufDeserializerTest, reuseMessages ){
//    auto add = m_data.user()->add();
//    auto req = new ClientRequest();
//    auto dat = QByteArray();

//    set_data(add);

//    m_data.serialize();
//    res_sut.parseClientRequest(dat, req);

//    ASSERT_TRUE(req->has_user());
//    auto addReq = req->user()->add();

//    EXPECT_EQ(add->get_nickname(),      addReq->get_nickname());
//    EXPECT_EQ(add->get_password(),      addReq->get_password());
//    EXPECT_EQ(add->get_email(),         addReq->get_email());
//    EXPECT_EQ(add->get_avatar(),        addReq->get_avatar());
//    EXPECT_EQ(add->get_phoneNumber(),   addReq->get_phoneNumber());
//    EXPECT_EQ(add->get_description(),   addReq->get_description());

//    delete req;
//}
