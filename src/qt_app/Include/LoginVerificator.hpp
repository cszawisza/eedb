#pragma once

#include "ILoginVerificator.hpp"

namespace requests{
namespace user{
class ILogin;
}
}


class LoginVerificator : public ILoginVerificator
{
public slots:
    void loginResponseReceived(const responses::user::ILogin &msg) const override;
};
