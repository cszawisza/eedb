#pragma once

#include "../StructuresCommon.hpp"
#include <QFlags>

class IAcl;

namespace responses{
namespace user{

enum Action{
    Action_Add,
    Action_Get,
    Action_Modify,
    Action_Delete,
    Action_ChengePassword,
};


class IAdd{
public:
    enum AddError{
        Error_noError               = 0,
        Error_BadName               = 1<<0,
        Error_BadEmail              = 1<<1,
        Error_MissingRequiredFields = 1<<2,
        Error_UserExists            = 1<<3
    };
    Q_DECLARE_FLAGS(AddErrors, AddError)

    virtual ~IAdd() = default;

    virtual bool is_successful() const = 0;
    virtual void set_successful( bool is_successful = true) = 0;

    virtual bool is_not_successful() const = 0;
    virtual void set_error( AddErrors code ) = 0;
    virtual AddErrors get_error_code() const = 0;
};

class ILogin{
public:
    enum LoginError{
        noError,
        Error_WrongNameOrPass = 1<<0,
        Error_UserOnline      = 1<<1,
        Error_UserDontExists  = 1<<2,
    };
    Q_DECLARE_FLAGS(LoginErrors, LoginError)

    virtual ~ILogin() = default;

    virtual bool is_successful() const = 0;
    virtual void set_successful( bool is_successful = true ) = 0;

    virtual bool is_not_successful() const = 0;
    virtual void set_error( LoginErrors code ) = 0;
    virtual LoginErrors get_error_code() const = 0;
};

class IModify{
public:
    virtual ~IModify() = default;
};

class IGet{
public:
    virtual ~IGet() = default;
};

}

class IUser{
public:
    virtual ~IUser() = default;

    //! returns stored action type or none
    virtual boost::optional<user::Action> stored_action() const = 0;
    virtual void clear_action(){}

    virtual bool has_add() const {return false;}
    virtual bool has_login() const {return false;}
    virtual bool has_get() const {return false;}

    virtual user::IAdd* add() { return nullptr; }
    virtual user::ILogin* login() {return nullptr; }
    virtual user::IGet* get() { return nullptr; }

    virtual const user::IAdd& get_add() const = 0;
    virtual const user::ILogin& get_login() const = 0;
    virtual const user::IGet& get_get() const = 0;
};
}

Q_DECLARE_OPERATORS_FOR_FLAGS(responses::user::IAdd::AddErrors)
Q_DECLARE_OPERATORS_FOR_FLAGS(responses::user::ILogin::LoginErrors)
