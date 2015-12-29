#include "ClientRequestAdapter.hpp"
#include "UserRequestAdapter.hpp"
#include "message_conteiner.pb.h"

using namespace requests;
using namespace requests::user;

ClientRequest::ClientRequest():
    m_data(new protobuf::ClientRequest() ), m_takeOvnership(true), m_userreq(nullptr)
{

}

ClientRequest::ClientRequest(protobuf::ClientRequest *req):
    m_data(req), m_takeOvnership(false), m_userreq(nullptr)
{

}

ClientRequest::~ClientRequest()
{
    if(m_takeOvnership){
        delete m_data;
        if(m_userreq)
            delete m_userreq;
    }
}

int ClientRequest::get_requestId() const
{
}

requests::IUser* ClientRequest::user()
{
    if(!m_userreq)
        m_userreq = new User(m_data->mutable_userreq());
    else
        m_userreq->operator =( User(m_data->mutable_userreq()));
    return m_userreq;
}

const IUser &ClientRequest::get_user() const
{
    if(!m_userreq)
        m_userreq = new User(const_cast<protobuf::UserReq*>(&m_data->userreq()));
    else
        m_userreq->operator=( User(const_cast<protobuf::UserReq*>(&m_data->userreq())));
    return *m_userreq;
}

void ClientRequest::assign(requests::IUser *ur)
{
    m_data->set_allocated_userreq( dynamic_cast<User*>(ur)->detachData() );
    delete ur;
}

bool ClientRequest::has_user() const
{
    return m_data->has_userreq();
}

void ClientRequest::clear_user()
{
    m_data->clear_userreq();
}

protobuf::ClientRequest *ClientRequest::rawPointer() const
{
    return m_data;
}


void ClientRequest::parse(const QByteArray &data)
{
    m_data->ParseFromArray(data.data(), data.size());
}

QByteArray ClientRequest::serialize() const
{
    QByteArray ba;
    ba.resize(m_data->ByteSize());
    m_data->SerializePartialToArray(ba.data(), ba.size());
    return ba;
}


ICategory *ClientRequest::category()
{
}

const ICategory &ClientRequest::get_category() const
{
}

void ClientRequest::assign(ICategory *ur)
{

}

bool ClientRequest::has_category() const
{
}

void ClientRequest::clear_category()
{
}
