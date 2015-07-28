#pragma once

#include "ILoginVerificator.hpp"

class QWebSocket;

class LoginVerificator : public ILoginVerificator
{
public:
    LoginVerificator(QWebSocket &);
    bool wasLoginSucces() const override;
private:
    QWebSocket & m_qWebSocket;
};
