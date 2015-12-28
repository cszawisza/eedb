#pragma once

#include "../StructuresCommon.hpp"
#include <QFlags>

class IAcl;

namespace responses{
namespace user{

class IAdd{
public:
    enum AddError{
        Error_noError       = 0,
        Error_NameToShort   = 1<<0,
        Error_BadEmail      = 1<<1
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
        Error_noError,
        Error_WrongNameOrPass
    };
    Q_DECLARE_FLAGS(LoginErrors, LoginError)

    virtual ~ILogin() = default;

    virtual bool is_successful() const = 0;
    virtual void set_successful() = 0;

    virtual bool is_not_successful() const = 0;
    virtual void set_error( LoginError code ) = 0;
    virtual LoginError get_error_code() const = 0;
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

    virtual user::IAdd* add() =0;
    virtual void assign( user::IAdd* ) = 0;
    virtual bool has_add() const = 0;
    virtual void clear_add() = 0;

    virtual user::ILogin* login() =0;
    virtual void assign( user::ILogin* ) = 0;
    virtual bool has_login() const = 0;
    virtual void clear_login() = 0;

    virtual user::IGet* get() = 0;
    virtual void assign( user::IGet* ) = 0;
    virtual bool has_get() const = 0;
    virtual void clear_get() = 0;
};
}

Q_DECLARE_OPERATORS_FOR_FLAGS(responses::user::IAdd::AddErrors)
Q_DECLARE_OPERATORS_FOR_FLAGS(responses::user::ILogin::LoginErrors)
