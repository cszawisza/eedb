#pragma once

#include "TextFieldValidator.hpp"

class NickNameValidator : public TextFieldValidator {
public:
    NickNameValidator();
    virtual bool isValid(const String &data) const;
};

