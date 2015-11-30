#pragma once

#include "../Interfaces/UserData.hpp"

#include <regex>

namespace data{

template<>
bool hasRequiredFields( const requests::user::IAdd &m_data ){
    bool hasRequiredFileds = m_data.has_email() &&
            m_data.has_password() &&
            m_data.has_nickname();
    if(!hasRequiredFileds)
        return false;
    return true;
}

constexpr auto emailRegexp  = "(?:[a-z0-9!#$%&'*+/=?^_`{|}~-]+(?:\\.[a-z0-9!#$%&'*+/=?^_`{|}~-]+)*|\"(?:[\\x01-\\x08\\x0b\\x0c\\x0e-\\x1f\\x21\\x23-\\x5b\\x5d-\\x7f]|\\\\[\\x01-\\x09\\x0b\\x0c\\x0e-\\x7f])*\")@(?:(?:[a-z0-9](?:[a-z0-9-]*[a-z0-9])?\\.)+[a-z0-9](?:[a-z0-9-]*[a-z0-9])?|\\[(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?|[a-z0-9-]*[a-z0-9]:(?:[\\x01-\\x08\\x0b\\x0c\\x0e-\\x1f\\x21-\\x5a\\x53-\\x7f]|\\\\[\\x01-\\x09\\x0b\\x0c\\x0e-\\x7f])+)\\])";

template<>
bool isValid( const requests::user::IAdd &data ){
    ///TODO add email validation
    auto &email = data.get_email();
    if( !std::regex_match (email, std::regex(emailRegexp) ) )
        return false;

    return true;
}

template<>
bool isValid(const requests::user::ILogin &m_data){
    return m_data.has_credentials() !=0 &&
            m_data.has_password();
}
}
