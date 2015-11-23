#pragma once

#include <string>

#include "ILoginVerificator.hpp"
#include "ICommunicationManager.hpp"
#include <QSharedPointer>

class LoginVerificator : public ILoginVerificator
{
public:
    LoginVerificator();
    bool tryLogin(const std::string &, const std::string &) const override;
};
