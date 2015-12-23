#include "TextFieldValidator.hpp"

TextFieldValidator::TextFieldValidator():
    TextFieldValidator(0, 100000)
{
}

TextFieldValidator::TextFieldValidator(size_t minLength, size_t maxLength):
    m_minNickNameLength(minLength), m_maxNickNameLength(maxLength)
{
}

bool TextFieldValidator::isValid(const String &data) const
{
    return hasValidLength(data);
}

bool TextFieldValidator::isValid(const QString &data) const
{
    return isValid(data.toStdString());
}

bool TextFieldValidator::hasValidLength(const String &data) const
{
    auto len = data.length();
    if( len > maxNickNameLength() ||
            len < minNickNameLength() ){
        return false;
    }
    return true;
}

bool TextFieldValidator::isValid(const char *data) const
{
    return isValid( String(data));
}

size_t TextFieldValidator::maxNickNameLength() const
{
    return m_maxNickNameLength;
}

void TextFieldValidator::setMaxNickNameLength(const size_t &maxNickNameLength)
{
    m_maxNickNameLength = maxNickNameLength;
}

size_t TextFieldValidator::minNickNameLength() const
{
    return m_minNickNameLength;
}

void TextFieldValidator::setMinNickNameLength(const size_t &minNickNameLength)
{
    m_minNickNameLength = minNickNameLength;
}
