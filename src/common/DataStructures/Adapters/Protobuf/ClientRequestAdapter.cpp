#include "ClientRequestAdapter.hpp"
#include "UserAdapter.hpp"
#include "message_conteiner.pb.h"


ProtobufClientRequestAdapter::ProtobufClientRequestAdapter():
    m_data(new pb::ClientRequest() ), m_takeOvnership(true)
{

}

ProtobufClientRequestAdapter::ProtobufClientRequestAdapter(pb::ClientRequest *req):
    m_data(req), m_takeOvnership(false)
{

}

ProtobufClientRequestAdapter::~ProtobufClientRequestAdapter()
{
    if(m_takeOvnership)
        delete m_data;
}

int ProtobufClientRequestAdapter::get_requestId() const
{
}

std::unique_ptr<data::requests::IUser> ProtobufClientRequestAdapter::user()
{
    return std::make_unique<ProtobufUserAdapter>(m_data->mutable_userreq());
}

void ProtobufClientRequestAdapter::assign_user(data::requests::IUser *ur)
{
//    this->set_allocated_userreq( static_cast<ProtobufUserAdapter*>(ur) );
}

bool ProtobufClientRequestAdapter::has_user() const
{
    return m_data->has_userreq();
}

void ProtobufClientRequestAdapter::clear_user()
{
    m_data->clear_userreq();
}

pb::ClientRequest *ProtobufClientRequestAdapter::rawPointer() const
{
    return m_data;
}
