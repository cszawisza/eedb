#pragma once

#include <string>
#include <ILoginVerificator.hpp>

class LoginVerificatorMock : public ILoginVerificator
{
public:
    MOCK_CONST_METHOD2(tryLogin, bool(const std::string &, const std::string &));
};
