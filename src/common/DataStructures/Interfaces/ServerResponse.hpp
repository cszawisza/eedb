#pragma once

#include <memory>


namespace requests{
    class IUser;
}

class IServerResponse{
public:
    virtual ~IServerResponse() = default;

    virtual void set_response_id( uint64_t id ) = 0;
    virtual void set_in_response_to( uint64_t id) = 0;
    ///TODO add some enum with normal statuses
    virtual void set_response_code( int code ) = 0;
//    virtual int get_requestId() const = 0;

//    virtual std::unique_ptr<requests::IUser> user() =0;
//    virtual void assign_user( requests::IUser* ) = 0;
//    virtual bool has_user() const = 0;
//    virtual void clear_user() = 0;
};

//class IServerResponseContainer {
//public:
//    virtual ~IServerResponseContainer() = default;

////    virtual std::shared_ptr<IClientRequest> newClientRequest() = 0;
////    virtual int requests_size() const =0;

//};

