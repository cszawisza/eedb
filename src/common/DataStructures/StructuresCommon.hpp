#pragma once

#include <boost/variant.hpp>
#include <boost/optional.hpp>
#include <boost/none.hpp>

#include <string>
#include <array>
#include <type_traits>

#include <QString>

using Int64 = int64_t;
using UInt64 = uint64_t;
using UID = uint64_t;
using Bytes = std::string;
using String = std::string;
using Email = std::string;

enum Status{

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

template <typename ID>
class NamedIdentyfier
{
    public:
        constexpr NamedIdentyfier(const ID& val) : _value(val), _name(""){}
        constexpr NamedIdentyfier(const ID& val, const char *name) : _value(val), _name(name) {}
        constexpr ID getId() const {return _value;}
        constexpr char *getName() const {return _name;}

        constexpr bool operator == ( const NamedIdentyfier &other ) const { return this->getId() == other.getId(); }
        constexpr bool operator <  ( const NamedIdentyfier &other ) const { return this->getId() < other.getId();}
        constexpr bool operator >  ( const NamedIdentyfier &other ) const { return !this->operator <( other ) && !this->operator ==( other); }
        constexpr bool operator >= ( const NamedIdentyfier &other ) const { return this->operator >( other ) || this->operator ==( other ); }
        constexpr bool operator <= ( const NamedIdentyfier &other ) const { return this->operator <( other ) || this->operator ==( other ); }
        constexpr bool operator != ( const NamedIdentyfier &other ) const { return !this->operator ==(other); }
    protected:
        ID _value;
        const char *_name;
};

using CategoryTypeId = NamedIdentyfier<int>;
using ActionId = NamedIdentyfier<int>;

//constexpr ActionId UserAdd = ActionId(1, "user::action::add");
