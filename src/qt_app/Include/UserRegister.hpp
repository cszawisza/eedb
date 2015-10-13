#pragma once

#include "IUserRegister.hpp"

class QWebSocket;

class UserRegister : public IUserRegister
{
public:
    UserRegister(QWebSocket &);
    void registerUser() const override;

private:
    QWebSocket & m_qWebSocket;
};
