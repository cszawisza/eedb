#pragma once

#include "../UserData.hpp"

namespace data{

template<>
bool isValid( const requests::user::Add &m_data ){
    bool hasRequiredFileds = m_data.email.is_initialized() &&
            m_data.password.is_initialized() &&
            m_data.name.is_initialized();
    if(!hasRequiredFileds)
        return false;

    if( m_data.email.get().isNotValid() )
        return false;
    return true;
}

template<>
bool isValid(const requests::user::Login &m_data){
    return m_data.cred.data.which() !=0 &&
            m_data.password.is_initialized();
}
}
