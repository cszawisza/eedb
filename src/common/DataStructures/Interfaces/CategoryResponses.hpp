#pragma once

#include "../StructuresCommon.hpp"
#include <QFlags>

namespace responses{
namespace category{

enum Action{
    Action_Add,
    Action_Get,
    Action_Modify,
    Action_Delete,
};

class IAdd {
public:
    ~IAdd() = default;

    enum AddError{
        NoErrors = 0,
        Error_NameMissing = 1<<0,
    };
    Q_DECLARE_FLAGS(AddErrors, AddError)

    virtual void set_code( AddErrors ) = 0;
};

class IGet {
public:
    virtual ~IGet() = default;  
    enum GetError{
        NoErrors = 0,
    };
    Q_DECLARE_FLAGS(GetErrors, GetError)

    virtual void set_code( GetErrors ) = 0;
};

}

class ICategory{
public:
    ~ICategory() = default;

    //! returns stored action type or none
    virtual boost::optional<category::Action> stored_action() const = 0;
    virtual void clear_action(){}

    virtual bool has_add() const {return false;}
    virtual bool has_get() const {return false;}

    virtual category::IAdd* add() { return nullptr; }
    virtual category::IGet* get() { return nullptr; }

    virtual const category::IAdd& get_add() const {}
    virtual const category::IGet& get_get() const {}
};

}

Q_DECLARE_OPERATORS_FOR_FLAGS(responses::category::IAdd::AddErrors)
Q_DECLARE_OPERATORS_FOR_FLAGS(responses::category::IGet::GetErrors)
