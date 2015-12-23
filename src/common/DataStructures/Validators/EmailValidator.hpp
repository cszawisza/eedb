#pragma once

#include "TextFieldValidator.hpp"

class EmailValidator : public TextFieldValidator {
    // IValidator interface
public:
    virtual bool isValid( const String &data ) const override;
};

