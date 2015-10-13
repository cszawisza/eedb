#pragma once

#include <IUserRegister.hpp>

class UserRegisterMock : public IUserRegister
{
public:
     MOCK_CONST_METHOD0(registerUser, void());
};
