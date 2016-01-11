#include "ClientRequestAdapter.hpp"

#include "UserRequestAdapter.hpp"
#include "CategoryRequestAdapter.hpp"

#include "message_conteiner.pb.h"

using namespace requests;
using namespace requests::user;
using namespace requests::category;

ClientRequest::ClientRequest():
    m_data(new protobuf::ClientRequest() ), m_takeOvnership(true), m_userreq(nullptr), m_catreq(nullptr)
{

}

ClientRequest::ClientRequest(protobuf::ClientRequest *req):
    m_data(req), m_takeOvnership(false), m_userreq(nullptr), m_catreq(nullptr)
{

}

ClientRequest::~ClientRequest()
{
    if(m_takeOvnership){
        delete m_data;
    }
    if(m_userreq)
        delete m_userreq;
    if(m_catreq)
        delete m_catreq;
}

int ClientRequest::get_requestId() const
{
    return m_data->request_id();
}

Optional<CategoryTypeId> ClientRequest::message_type() const
{
    using protobuf::ClientRequest;

    switch (m_data->data_case()) {
    case ClientRequest::kUserReq:
        return clientRequestsUser;
    case ClientRequest::kCategoryReq:
        return clientRequestsCategory;
    default:
        return boost::none;
    }
}

IUser *ClientRequest::user()
{
    if(!m_userreq)
        m_userreq = new requests::User(m_data->mutable_userreq());
    else
        m_userreq->operator =( requests::User(m_data->mutable_userreq()));
    return m_userreq;
}

const IUser &ClientRequest::get_user() const
{
    if(!m_userreq)
        m_userreq = new requests::User(const_cast<protobuf::UserReq*>(&m_data->userreq()));
    else
        m_userreq->operator=( requests::User(const_cast<protobuf::UserReq*>(&m_data->userreq())));
    return *m_userreq;
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
    if(!m_catreq)
        m_catreq = new requests::Category(m_data->mutable_categoryreq());
    else
        m_catreq->operator =( requests::Category(m_data->mutable_categoryreq()));
    return m_catreq;
}

const ICategory &ClientRequest::get_category() const
{
    if(!m_catreq)
        m_catreq = new requests::Category(const_cast<protobuf::CategoryReq*>(&m_data->categoryreq()));
    else
        m_catreq->operator=( requests::Category(const_cast<protobuf::CategoryReq*>(&m_data->categoryreq())));
    return *m_catreq;
}

bool ClientRequest::has_category() const
{
    return m_data->has_categoryreq();
}

void ClientRequest::clear_category()
{
    m_data->clear_categoryreq();
}
