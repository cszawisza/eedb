#pragma once

#include <string>

#include "ILoginVerificator.hpp"

class QWebSocket;

class LoginVerificator : public ILoginVerificator
{
public:
    LoginVerificator(QWebSocket &);
    bool tryLogin(const std::string &, const std::string &) const override;

private:
    QWebSocket & m_qWebSocket;
};
