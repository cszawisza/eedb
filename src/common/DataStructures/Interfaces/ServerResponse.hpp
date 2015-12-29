#pragma once

#include "../StructuresCommon.hpp"

namespace responses{
    class IUser;
}

class IServerResponse{
public:
    virtual ~IServerResponse() = default;

    virtual void parse(const QByteArray &data) = 0;
    virtual QByteArray serialize() const = 0;

    virtual void set_response_id( UID id ) = 0;
    virtual void set_in_response_to( UID id) = 0;
    ///TODO add some enum with normal statuses
    virtual void set_response_code( int code ) = 0;
//    virtual int get_requestId() const = 0;

    virtual void assign( responses::IUser* user) = 0;
    virtual responses::IUser* user() =0;
    virtual bool has_user() const = 0;
    virtual void clear_user() = 0;
};
