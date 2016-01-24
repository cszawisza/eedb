#pragma once

#include "IUserRegister.hpp"

class IUserCommunicationManager;

class UserRegister : public IUserRegister
{
    Q_OBJECT
public:
    UserRegister(/*ICommunicationManager &*/);
    void registerUser() const override;

private:
//    ICommunicationManager & m_communicatioManager;
};
