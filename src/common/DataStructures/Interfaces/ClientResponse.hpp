#pragma once

namespace responses{
    class IUser;
}

class IClientRequest{
public:
    virtual ~IClientRequest() = default;

    virtual int get_requestId() const = 0;

    virtual responses::IUser* user() =0;
    virtual void assign_user( responses::IUser* ) = 0;
    virtual bool has_user() const = 0;
    virtual void clear_user() = 0;
};
