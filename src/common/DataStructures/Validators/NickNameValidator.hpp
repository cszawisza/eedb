#pragma once

#include "TextFieldValidator.hpp"

namespace data{
class NickNameValidator : public TextFieldValidator {
public:
    NickNameValidator();
    virtual bool isValid(const String &data) const;
};
}
