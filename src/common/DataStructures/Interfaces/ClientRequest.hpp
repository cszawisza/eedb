#pragma once

#include "../StructuresCommon.hpp"
#include "CommonDefinitions.hpp"


namespace requests{
    class IUser;
    class ICategory;
}

class QByteArray;
class IRequestParser;

class IClientRequest{
public:
    virtual ~IClientRequest() = default;

    virtual void parse(const QByteArray &data) = 0;
    virtual QByteArray serialize() const = 0;

    virtual int get_requestId() const = 0;

    virtual Optional<MessageType> message_type() const { return boost::none; }

    virtual requests::IUser* user() { return nullptr;}
    virtual const requests::IUser& get_user() const = 0;
    virtual bool has_user() const = 0;
    virtual void clear_user() = 0;

    virtual requests::ICategory* category() =0;
    virtual const requests::ICategory& get_category() const = 0;
    virtual bool has_category() const = 0;
    virtual void clear_category() = 0;

//    virtual void assign( requests::ICategory* ) = 0;
//    virtual void assign( requests::IUser* ) = 0;
};
