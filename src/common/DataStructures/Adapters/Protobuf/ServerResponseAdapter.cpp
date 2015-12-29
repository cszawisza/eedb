#include "ServerResponseAdapter.hpp"
#include "UserResponseAdapter.hpp"
#include "message_conteiner.pb.h"

ServerResponse::ServerResponse():
    m_data(new protobuf::ServerResponse(protobuf::ServerResponse::default_instance()) ), m_takeOvnership(true), m_user(nullptr)
{

}

ServerResponse::ServerResponse(protobuf::ServerResponse *req):
    m_data(req), m_takeOvnership(false), m_user(nullptr)
{

}

ServerResponse::~ServerResponse()
{
    if(m_takeOvnership)
        delete m_data;
    if(m_user)
        delete m_user;
}

void ServerResponse::set_response_id(uint64_t id)
{
    m_data->set_response_id(id);
}

void ServerResponse::set_in_response_to(uint64_t id)
{
    m_data->set_in_response_to(id);
}

void ServerResponse::set_response_code(int code)
{
    m_data->set_code(code);
}

responses::IUser *ServerResponse::user()
{
    if(!m_user)
        m_user = new responses::User(m_data->mutable_userres());
    else
        m_user->operator=(responses::User(m_data->mutable_userres()));
    return m_user;
}

void ServerResponse::assign(responses::IUser *ur)
{
    m_data->set_allocated_userres( dynamic_cast<responses::User*>(ur)->detachData() );
    delete ur;
}

bool ServerResponse::has_user() const
{
    return m_data->has_userres();
}

void ServerResponse::clear_user()
{
    m_data->clear_userres();
}

protobuf::ServerResponse *ServerResponse::rawPointer() const
{
    return m_data;
}

void ServerResponse::parse(const QByteArray &data)
{
    m_data->ParseFromArray(data.data(),data.size());
}

QByteArray ServerResponse::serialize() const
{
    int size = m_data->ByteSize();

    QByteArray ba;
    ba.resize(size);
    m_data->SerializePartialToArray(ba.data(), size);
    return ba;
}
