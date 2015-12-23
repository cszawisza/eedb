#include "ClientRequestAdapter.hpp"
#include "UserAdapter.hpp"
#include "message_conteiner.pb.h"

using namespace requests;
using namespace requests::user;

ProtobufClientRequestAdapter::ProtobufClientRequestAdapter():
    m_data(new pb::ClientRequest() ), m_takeOvnership(true), m_userreq(nullptr)
{

}

ProtobufClientRequestAdapter::ProtobufClientRequestAdapter(pb::ClientRequest *req):
    m_data(req), m_takeOvnership(false), m_userreq(nullptr)
{

}

ProtobufClientRequestAdapter::~ProtobufClientRequestAdapter()
{
    if(m_takeOvnership){
        delete m_data;
        if(m_userreq)
            delete m_userreq;
    }
}

int ProtobufClientRequestAdapter::get_requestId() const
{
}

requests::IUser* ProtobufClientRequestAdapter::user()
{
    if(!m_userreq)
        m_userreq = new ProtobufUserAdapter(m_data->mutable_userreq());
    else
        m_userreq->operator =( ProtobufUserAdapter(m_data->mutable_userreq()));
    return m_userreq;
}

void ProtobufClientRequestAdapter::assign_user(requests::IUser *ur)
{
    m_data->set_allocated_userreq( dynamic_cast<ProtobufUserAdapter*>(ur)->detachData() );
    delete ur;
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
