#pragma once

#include "../Validators/IValidator.hpp"
#include <memory>

namespace data{

class EmailValidator;
class NickNameValidator;

namespace requests{
namespace user{
class IAdd;
class ILogin;
}
}

class UserAddValidator : public IMessageValidator<requests::user::IAdd>{

public:
    UserAddValidator();
    bool isValid(const requests::user::IAdd &data) const override;
    bool hasRequiredFields( const requests::user::IAdd &m_data ) const override;

    void setEmailValidator( std::shared_ptr<EmailValidator> validator);
    void setNickNameValidator( std::shared_ptr<NickNameValidator> validator);
private:
    std::shared_ptr<EmailValidator> m_emailValidator;
    std::shared_ptr<NickNameValidator> m_nameValidator;
};

class UserLoginValidator : public IMessageValidator<requests::user::ILogin>{
public:
    bool isValid(const requests::user::ILogin &data) const;
    bool hasRequiredFields(const requests::user::ILogin &data) const;
};

}
