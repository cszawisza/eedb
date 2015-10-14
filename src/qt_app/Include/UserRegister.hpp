#pragma once

#include "IUserRegister.hpp"

class ICommunicationManager;

class UserRegister : public IUserRegister
{
public:
    UserRegister(ICommunicationManager &);
    void registerUser() const override;

private:
    ICommunicationManager & m_communicatioManager;
};
