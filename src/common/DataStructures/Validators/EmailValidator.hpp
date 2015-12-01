#pragma once

#include "TextFieldValidator.hpp"

namespace data{

class EmailValidator : public TextFieldValidator {
    // IValidator interface
public:
    virtual bool isValid( const data::String &data ) const override;
};

}
