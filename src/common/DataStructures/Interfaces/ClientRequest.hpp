#pragma once

#include "../StructuresCommon.hpp"

namespace requests{
    class IUser;
    class ICategory;
    class IItem;
}

class QByteArray;
class IRequestParser;

class IClientRequest : public ISerializableData, public IMessageContainer{
public:
    virtual ~IClientRequest() = default;

    virtual int get_requestId() const = 0;

    virtual requests::IUser* user() { return nullptr; }
    virtual const requests::IUser& get_user() const = 0;
    virtual bool has_user() const = 0;
    virtual void clear_user() = 0;

    virtual requests::ICategory* category() { return nullptr; }
    virtual const requests::ICategory& get_category() const = 0;
    virtual bool has_category() const = 0;
    virtual void clear_category() = 0;
};
