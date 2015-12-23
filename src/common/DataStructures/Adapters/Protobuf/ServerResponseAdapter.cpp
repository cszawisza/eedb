#include "ServerResponseAdapter.hpp"

#include "message_conteiner.pb.h"

ProtobufServerResponseAdapter::ProtobufServerResponseAdapter():
    m_data(new pb::ServerResponse(pb::ServerResponse::default_instance()) ), m_takeOvnership(true)
{

}

ProtobufServerResponseAdapter::ProtobufServerResponseAdapter(pb::ServerResponse *req):
    m_data(req), m_takeOvnership(false)
{

}

ProtobufServerResponseAdapter::~ProtobufServerResponseAdapter()
{
    if(m_takeOvnership)
        delete m_data;
}

void ProtobufServerResponseAdapter::set_response_id(uint64_t id)
{
    m_data->set_response_id(id);
}

void ProtobufServerResponseAdapter::set_in_response_to(uint64_t id)
{
    m_data->set_in_response_to(id);
}

void ProtobufServerResponseAdapter::set_response_code(int code)
{
    m_data->set_code(code);
}

requests::IUser *ProtobufServerResponseAdapter::user()
{
///FIXME
}

void ProtobufServerResponseAdapter::assign_user(requests::IUser *ur)
{
///FIXME
}

bool ProtobufServerResponseAdapter::has_user() const
{
    return m_data->has_userres();
}

void ProtobufServerResponseAdapter::clear_user()
{
    m_data->clear_userres();
}

pb::ServerResponse *ProtobufServerResponseAdapter::rawPointer() const
{
    return m_data;
}
