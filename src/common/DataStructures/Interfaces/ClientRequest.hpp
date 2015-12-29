#pragma once

namespace requests{
    class IUser;
}

class QByteArray;
class IRequestParser;

class IClientRequest{
public:
    virtual ~IClientRequest() = default;

    virtual void parse(const QByteArray &data) = 0;
    virtual QByteArray serialize() const = 0;

    virtual int get_requestId() const = 0;

    virtual requests::IUser* user() =0;
    virtual void assign_user( requests::IUser* ) = 0;
    virtual const requests::IUser& get_user() const = 0;
    virtual bool has_user() const = 0;
    virtual void clear_user() = 0;
};
