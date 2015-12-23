#pragma once

namespace requests{
    class IUser;
}

class IClientRequest{
public:
    virtual ~IClientRequest() = default;

    virtual int get_requestId() const = 0;

    virtual requests::IUser* user() =0;
    virtual void assign_user( requests::IUser* ) = 0;
    virtual bool has_user() const = 0;
    virtual void clear_user() = 0;
};
