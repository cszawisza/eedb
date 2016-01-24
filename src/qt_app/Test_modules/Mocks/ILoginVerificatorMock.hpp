#pragma once
#include "gmock/gmock.h"
#include <ILoginVerificator.hpp>

class ILoginVerificatorMock : public ILoginVerificator
{
    Q_OBJECT
public slots:
    void loginResponseReceived(const responses::user::ILogin &msg) const = 0;
};


class LoginVerificatorMock : public ILoginVerificatorMock
{
    Q_OBJECT
public:
    MOCK_CONST_METHOD1_T(loginResponseReceived, void(const responses::user::ILogin &));
};
