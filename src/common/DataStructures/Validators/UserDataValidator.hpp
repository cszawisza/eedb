#pragma once

#include "../Interfaces/UserData.hpp"

#include "EmailValidator.hpp"
#include <memory>

namespace data{
class UserAddValidator : public IMessageValidator<requests::user::IAdd>{

public:
    UserAddValidator();
    bool isValid(const requests::user::IAdd &data) const override;
    bool hasRequiredFields( const requests::user::IAdd &m_data ) const override;

    void setEmailValidator( std::shared_ptr<EmailValidator> validator);

private:
    std::shared_ptr<EmailValidator> m_emailValidator;
};

//template<>
//bool isValid(const requests::user::ILogin &m_data){
//    return m_data.has_credentials() !=0 &&
//            m_data.has_password();
//}

}
