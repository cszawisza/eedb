#include "UserDataValidator.hpp"

using namespace data;
using namespace std;
UserAddValidator::UserAddValidator():
    m_emailValidator( make_shared<EmailValidator>() )
{

}

bool UserAddValidator::isValid(const requests::user::IAdd &data ) const{
    auto const &email = data.get_email();

    if(!m_emailValidator->isValid(email))
        return false;
    return true;
}

bool UserAddValidator::hasRequiredFields(const requests::user::IAdd &m_data) const{
    bool hasRequiredFileds = m_data.has_email() &&
            m_data.has_password() &&
            m_data.has_nickname();
    if(!hasRequiredFileds)
        return false;
    return true;
}

void UserAddValidator::setEmailValidator(std::shared_ptr<EmailValidator> validator){
    m_emailValidator.swap(validator);
}

