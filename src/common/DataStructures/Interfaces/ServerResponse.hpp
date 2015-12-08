#pragma once

#include <memory>

namespace data{
namespace requests{
    class IUser;
}

class IServerResponse{
public:
    virtual ~IServerResponse() = default;

//    virtual int get_requestId() const = 0;

//    virtual std::unique_ptr<data::requests::IUser> user() =0;
//    virtual void assign_user( requests::IUser* ) = 0;
//    virtual bool has_user() const = 0;
//    virtual void clear_user() = 0;
};

class IServerResponseContainer {
public:
    virtual ~IServerResponseContainer() = default;

//    virtual std::shared_ptr<IClientRequest> newClientRequest() = 0;
//    virtual int requests_size() const =0;

};

}
