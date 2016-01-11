#pragma once

#include "../StructuresCommon.hpp"
#include "CommonDefinitions.hpp"
#include <QFlags>

namespace responses{
    class IUser;
    class ICategory;
}

class IServerResponse{
public:
    enum ResponseFlag{
        NoError             = 0,
        Error_UserOfline    = 1<<1,
        Error_AccesDeny     = 1<<2,
    };
    Q_DECLARE_FLAGS(ResponseFlags, ResponseFlag)

    virtual ~IServerResponse() = default;

    virtual void parse(const QByteArray &data) = 0;
    virtual QByteArray serialize() const = 0;

    virtual void set_response_id( UID id ) = 0;
    virtual void set_in_response_to( UID id) = 0;
    virtual void set_response_code( ResponseFlags code ) = 0;


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
