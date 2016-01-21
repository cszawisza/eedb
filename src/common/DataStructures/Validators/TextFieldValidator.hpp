#pragma once

#include "IValidator.hpp"
#include "../StructuresCommon.hpp"

class QString;

class TextFieldValidator : public IFieldValidator<String> {
public:
    TextFieldValidator();
    TextFieldValidator( size_t minLength, size_t maxLength );

    virtual bool isValid(const String &data) const;
    bool isValid( const QString &data ) const;
    bool isValid( const char* data) const;

    bool hasValidLength(const String &data) const;

    size_t maxTextLength() const;
    void setMaxTextLength(const size_t &textLength);

    size_t minTextLength() const;
    void setMinTextLength(const size_t &textLength);
private:
    size_t m_minNickNameLength;
    size_t m_maxNickNameLength;
};
