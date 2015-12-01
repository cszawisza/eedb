#include "EmailValidator.hpp"
#include "../StructuresCommon.hpp"

#include <regex>

constexpr auto emailRegexp  = "(?:[a-z0-9!#$%&'*+/=?^_`{|}~-]+(?:\\.[a-z0-9!#$%&'*+/=?^_`{|}~-]+)*|\"(?:[\\x01-\\x08\\x0b\\x0c\\x0e-\\x1f\\x21\\x23-\\x5b\\x5d-\\x7f]|\\\\[\\x01-\\x09\\x0b\\x0c\\x0e-\\x7f])*\")@(?:(?:[a-z0-9](?:[a-z0-9-]*[a-z0-9])?\\.)+[a-z0-9](?:[a-z0-9-]*[a-z0-9])?|\\[(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?|[a-z0-9-]*[a-z0-9]:(?:[\\x01-\\x08\\x0b\\x0c\\x0e-\\x1f\\x21-\\x5a\\x53-\\x7f]|\\\\[\\x01-\\x09\\x0b\\x0c\\x0e-\\x7f])+)\\])";

using namespace data;
bool EmailValidator::isValid(const data::String &data) const {
    auto &email = data;
    if( !std::regex_match (email, std::regex(emailRegexp) ) )
        return false;

    //        auto parts = split(email, '@');

    //        if( parts[0].length() >= 64 )
    //            return false;
    //        if( parts[1].length() > 190 )
    //            return false;
    return true;
}
