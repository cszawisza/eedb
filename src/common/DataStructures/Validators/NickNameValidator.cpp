#include "NickNameValidator.hpp"

#include <QString>

using namespace data;

constexpr auto notAllowedCharacters = "@";

NickNameValidator::NickNameValidator() : m_maxNickNameLength(100), m_minNickNameLength(2)
{

}

bool NickNameValidator::isValid(const String &data) const
{
    auto len = data.length();
    if( len > maxNickNameLength() ||
            len < minNickNameLength() ){
        return false;
    }

    if( data.find_first_of( notAllowedCharacters ) != std::string::npos )
        return false;

    return true;
}

bool NickNameValidator::isValid(const char *data) const
{
    return isValid( String(data));
}
size_t NickNameValidator::maxNickNameLength() const
{
    return m_maxNickNameLength;
}

void NickNameValidator::setMaxNickNameLength(const size_t &maxNickNameLength)
{
    m_maxNickNameLength = maxNickNameLength;
}
size_t NickNameValidator::minNickNameLength() const
{
    return m_minNickNameLength;
}

void NickNameValidator::setMinNickNameLength(const size_t &minNickNameLength)
{
    m_minNickNameLength = minNickNameLength;
}


