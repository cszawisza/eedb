#pragma once
#include "IValidator.hpp"
#include "../StructuresCommon.hpp"

namespace data{

class EmailValidator : public IFieldValidator<data::String> {
    // IValidator interface
public:
    virtual bool isValid( const data::String &data ) const override;

    template<typename T>
    bool isValid(const T &data) const{ return isValid(data.get_email()); }

    bool isValid( const QString &email ) const;
    bool isValid( const char* email ) const;
};
}
