#pragma once

#include "TextFieldValidator.hpp"

class NickNameValidator : public TextFieldValidator {
public:
    NickNameValidator();
    virtual bool isValid(const String &data) const;

    void setMaxNickNameLength( size_t length){ setMaxTextLength(length); }
    size_t MaxNickNameLength() const{ return maxTextLength(); }

    void setMinNickNameLength( size_t length){ setMinTextLength(length); }
    size_t MinNickNameLength() const{ return minTextLength(); }
};

