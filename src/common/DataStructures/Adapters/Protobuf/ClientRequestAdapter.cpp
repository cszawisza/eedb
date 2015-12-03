#include "ClientRequestAdapter.hpp"

#include "UserAdapter.hpp"

int ProtobufClientRequestAdapter::get_requestId() const
{
}

data::requests::IUser *ProtobufClientRequestAdapter::user()
{
    if(!has_user())
        this->set_allocated_userreq( new ProtobufUserAdapter() );
    return static_cast<data::requests::IUser*>( static_cast<ProtobufUserAdapter*>(mutable_userreq()));
}

void ProtobufClientRequestAdapter::assign_user(data::requests::IUser *ur)
{
    this->set_allocated_userreq( static_cast<ProtobufUserAdapter*>(ur) );
}

bool ProtobufClientRequestAdapter::has_user() const
{
    return ClientRequest::has_userreq();
}

void ProtobufClientRequestAdapter::clear_user()
{
    ClientRequest::clear_userreq();
}

data::IClientRequest *ProtobufClientRequestsAdapter::newClientRequest()
{
    m_requests.push_back( new ProtobufClientRequestAdapter );
    return m_requests.back();
}

int ProtobufClientRequestsAdapter::requests_size() const
{
    return ClientRequests::request_size();
}

void ProtobufClientRequestsAdapter::form()
{
    for(auto req: m_requests){
        this->add_request()->MergeFrom(*req);
    }
}
