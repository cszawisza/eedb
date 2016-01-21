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
    if( len >= maxTextLength() ||
            len <= minTextLength() ){
        return false;
    }
    return true;
}

bool TextFieldValidator::isValid(const char *data) const
{
    return isValid( String(data));
}

size_t TextFieldValidator::maxTextLength() const
{
    return m_maxNickNameLength;
}

void TextFieldValidator::setMaxTextLength(const size_t &textLength)
{
    m_maxNickNameLength = textLength;
}

size_t TextFieldValidator::minTextLength() const
{
    return m_minNickNameLength;
}

void TextFieldValidator::setMinTextLength(const size_t &textLength)
{
    m_minNickNameLength = textLength;
}
