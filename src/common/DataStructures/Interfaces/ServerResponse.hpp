#pragma once

#include "../StructuresCommon.hpp"
#include <QFlags>

namespace responses{
    class IUser;
    class ICategory;
}

class IServerResponse: public ISerialize/*, public IMessageType*/{
public:
    enum ResponseFlag{
        NoError             = 0,
        Error_UserOfline    = 1<<1,
        Error_AccesDeny     = 1<<2,
    };
    Q_DECLARE_FLAGS(ResponseFlags, ResponseFlag)

    virtual ~IServerResponse() = default;

    virtual void set_response_id( UID id ) = 0;
    virtual UID response_id() const = 0;

    virtual void set_in_response_to( UID id) = 0;
    virtual UID in_response_to() const = 0;

    virtual void set_response_code( ResponseFlags code ) = 0;
    virtual ResponseFlags response_code() const = 0;

    virtual responses::IUser* user() =0;
    virtual const responses::IUser& get_user() const = 0;
    virtual bool has_user() const = 0;
    virtual void clear_user() = 0;

    virtual responses::ICategory* category() =0;
    virtual const responses::ICategory& get_category() const = 0;
    virtual bool has_category() const=0;
    virtual void clear_category() =0;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(IServerResponse::ResponseFlags)
