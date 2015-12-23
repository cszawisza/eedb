#pragma once

#include "../StructuresCommon.hpp"

namespace requests{
namespace categories{

class IAdd {
    virtual String get_name() const = 0;
    virtual void set_name( String ) =0;
    virtual bool has_name() const = 0;
    virtual void clear_name() = 0;

    virtual UID get_parentId() const = 0;
    virtual void set_parentId( UID ) =0;
    virtual bool has_parentId() const = 0;
    virtual void clear_parentId() = 0;

    virtual String get_description() const = 0;
    virtual void set_description( String ) =0;
    virtual bool has_description() const = 0;
    virtual void clear_description() = 0;
};

}
}
