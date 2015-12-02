#pragma once

#include "IValidator.hpp"
#include "../StructuresCommon.hpp"

class QString;

///TODO add some tests for validator

namespace data{
class TextFieldValidator : public IFieldValidator<String> {
public:
    TextFieldValidator();
    TextFieldValidator( size_t minLength, size_t maxLength );
    virtual bool isValid(const String &data) const;
    bool isValid( const QString &data ) const;
    bool isValid( const char* data) const;

    bool hasValidLength(const String &data) const;

    size_t maxNickNameLength() const;
    void setMaxNickNameLength(const size_t &maxNickNameLength);

    size_t minNickNameLength() const;
    void setMinNickNameLength(const size_t &minNickNameLength);
private:
    size_t m_maxNickNameLength;
    size_t m_minNickNameLength;
};
}
