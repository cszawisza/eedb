#pragma once

#include "../StructuresCommon.hpp"

namespace requests{
namespace category{

class ICriterion{
public:
    virtual ~ICriterion() = default;

    virtual void request_all( bool request = true ) = 0;
    virtual bool has_requested_all() const = 0;
};

class IAdd {
public:
    ~IAdd() = default;

    virtual String get_name() const = 0;
    virtual void set_name( String name ) =0;
    virtual bool has_name() const = 0;
    virtual void clear_name() = 0;

    virtual UID get_parentId() const = 0;
    virtual void set_parentId( UID id) =0;
    virtual bool has_parentId() const = 0;
    virtual void clear_parentId() = 0;

    virtual String get_description() const = 0;
    virtual void set_description( String desc) =0;
    virtual bool has_description() const = 0;
    virtual void clear_description() = 0;
};

class IGet {
public:
    virtual ~IGet() = default;

    virtual bool has_requestedUid() const = 0;
    virtual void request_uid( bool request = true ) = 0;

    virtual bool has_requestedParentUid() const = 0;
    virtual void request_parentUid( bool request = true ) = 0;

    virtual bool has_requestedName() const = 0;
    virtual void request_name( bool request = true ) = 0;

//    virtual bool has_requestedDescription() const = 0;
//    virtual void request_description( bool request = true ) = 0;

//    virtual bool has_requestedAvatar() const = 0;
//    virtual void request_avatar( bool request = true ) = 0;

//    virtual bool has_requestedAcl() const = 0;
//    virtual void request_acl( bool request = true ) = 0;

//    virtual ICriterion *criteria() = 0;
//    virtual const ICriterion &get_criteria() const = 0;
};

}

class ICategory{
public:
    virtual ~ICategory() = default;
//    Optional<ActionId> ActionId

    virtual category::IAdd* add() =0;
    virtual const category::IAdd& get_add() const = 0;
    virtual bool has_add() const = 0;
    virtual void clear_add() = 0;

    virtual category::IGet* get() =0;
    virtual const category::IGet& get_get() const = 0;
    virtual bool has_get() const = 0;
    virtual void clear_get() = 0;
};

}
