#pragma once

#include "../StructuresCommon.hpp"
#include "../../utils/unixPerms.hpp"

namespace data{

class IAcl{
public:
    virtual ~IAcl() = default;

    virtual UID get_id() const = 0;
    virtual void set_id( UID ) = 0;
    virtual bool has_id() const = 0;
    virtual void clear_id() = 0;

    virtual UID get_owner() const = 0;
    virtual void set_owner( UID ) = 0;
    virtual bool has_owner() const = 0;
    virtual void clear_owner() = 0;

    virtual UID get_groups() const = 0;
    virtual void set_groups( UID ) = 0;
    virtual bool has_groups() const = 0;
    virtual void clear_groups() = 0;

    virtual UnixPermissions get_unixperms() const = 0;
    virtual void set_unixperms( UnixPermissions ) = 0;
    virtual bool has_unixperms() const = 0;
    virtual void clear_unixperms() = 0;

    virtual Status get_status() const = 0;
    virtual void set_status( Status ) = 0;
    virtual bool has_status() const = 0;
    virtual void clear_status() = 0;
};

}
