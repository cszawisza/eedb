#pragma once

#include <QFlags>

namespace responses{
namespace category{

class IAdd {
public:
    enum AddError{
        NoErrors = 0,
        Error_NameMissing = 1<<0,
    };
    Q_DECLARE_FLAGS(AddErrors, AddError)
    ~IAdd() = default;

    virtual void set_code( AddErrors ) = 0;
};

class IGet {
public:
    virtual ~IGet() = default;
};

}

class ICategory{
public:
    ~ICategory() = default;

    virtual category::IAdd* add() =0;
    virtual const category::IAdd& get_add() const = 0;
    virtual void assign( category::IAdd* ) = 0;
    virtual bool has_add() const = 0;
    virtual void clear_add() = 0;

};

}

Q_DECLARE_OPERATORS_FOR_FLAGS(responses::category::IAdd::AddErrors)
