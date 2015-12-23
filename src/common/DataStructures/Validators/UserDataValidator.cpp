#include "UserDataValidator.hpp"
#include "../Interfaces/UserRequests.hpp"

#include "EmailValidator.hpp"
#include "NickNameValidator.hpp"

#include <memory>

using namespace std;
namespace requests{
UserAddValidator::UserAddValidator():
    m_emailValidator( make_shared<EmailValidator>() ),
    m_nameValidator( make_shared<NickNameValidator>() )
{

}

bool UserAddValidator::isValid(const requests::user::IAdd &data ) const{
    auto const &email = data.get_email();
    auto const &name = data.get_nickname();

    if(!m_emailValidator->isValid(email))
        return false;
    if(!m_nameValidator->isValid(name))
        return false;

//    if( data.get_password().length() < 2 ){
//        addErrorCode(UserRes_Reply_PasswordToShort);
//        error = true;
//    }

//    if( basic.email().length() > 255 ){
//        addErrorCode(UserRes_Reply_EmailAddressToLong);
//        error = true;
//    }
//    if(!mailREX.exactMatch(QString::fromStdString(basic.email()))){
//        addErrorCode(UserRes_Reply_EmailNotValidate);
//        error = true;
//    }

//    // check optional fields
//    if( det.has_address() && det.address().length() >= 1000 ){
//        addErrorCode(UserRes_Reply_AddressToLong);
//        error = true;
//    }
//    if( basic.has_description() && basic.description().length() >= 100000 ){
//        addErrorCode(UserRes_Reply_DescriptionToLong);
//        error = true;
//    }
//    if( det.has_phone_number() && det.phone_number().length() >= 20 ){
//        addErrorCode(UserRes_Reply_BadPhoneNumber);
//        error = true;
//    }

    return true;
}

bool UserAddValidator::hasRequiredFields(const requests::user::IAdd &m_data) const{
    bool hasRequiredFileds =
            m_data.has_email() &&
            m_data.has_password() &&
            m_data.has_nickname();
    if(!hasRequiredFileds)
        return false;
    return true;
}

void UserAddValidator::setEmailValidator(std::shared_ptr<EmailValidator> validator){
    m_emailValidator.swap(validator);
}

void UserAddValidator::setNickNameValidator(std::shared_ptr<NickNameValidator> validator)
{
    m_nameValidator.swap(validator);
}
}
