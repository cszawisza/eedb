#pragma once

#include <QHash>

template <typename ID>
class NamedIdentyfier
{
    public:
        explicit constexpr NamedIdentyfier(const ID& val) : _value(val), _name(""){}
        constexpr NamedIdentyfier(const ID& val, const char *name) : _value(val), _name(name) {}
        constexpr ID getId() const {return _value; }
        constexpr const char *getName() const { return _name; }

        constexpr operator int () const { return _value; }

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

using ActionTypeId = NamedIdentyfier<int>;
using ActionId = NamedIdentyfier<int>;

template<typename T>
inline int qHash(const NamedIdentyfier<T> &val){
    return qHash(val.getId());
}
