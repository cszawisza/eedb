#include "NickNameValidator.hpp"

#include <QString>

constexpr auto notAllowedCharacters = "@";

NickNameValidator::NickNameValidator() :
    TextFieldValidator(2,100)
{
}

bool NickNameValidator::isValid(const String &data) const
{
    if( !hasValidLength(data) )
        return false;

    if( data.find_first_of( notAllowedCharacters ) != std::string::npos )
        return false;

    return true;
}
