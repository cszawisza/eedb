#pragma once

class IUserRegister
{
public:
    virtual void registerUser() const = 0;
    virtual ~IUserRegister() {}
};
