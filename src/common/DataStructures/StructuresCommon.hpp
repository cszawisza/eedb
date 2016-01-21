#pragma once

#include <boost/variant.hpp>
#include <boost/optional.hpp>
#include <boost/none.hpp>

#include <string>
#include <array>
#include <type_traits>
#include <memory>

#include <QString>
#include <QHash>

#include "../utils/NamedIdnetyfier.hpp"

using Int64 = int64_t;
using UInt64 = uint64_t;
using UID = uint64_t;
using Bytes = std::string;
using String = std::string;
using Email = std::string;

enum Status{
};

class IMessageContainer{
    virtual boost::optional<ActionTypeId> message_type() const = 0;
};

class IMessageActionContainer{
    virtual boost::optional<ActionId> action_type() const = 0;
};

class ISerialize{
    virtual void parse(const QByteArray &data) = 0;
    virtual QByteArray serialize() const = 0;
};

class  IAuthorizationData{
public:
    virtual ~IAuthorizationData() = default;

    virtual void set_authorization( boost::variant<String, UID> auth ) = 0;

    virtual bool is_authorized_by_email() const = 0;
    virtual bool is_authorized_by_nickname() const = 0;
    virtual bool is_authorized_by_id() const = 0;

    virtual const String &get_email() const =0;
    virtual const String &get_nickname() const =0;
    virtual UID           get_uid() const = 0;

    virtual void Clear() const = 0;
};
