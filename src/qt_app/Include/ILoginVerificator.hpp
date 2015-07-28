#pragma once

class ILoginVerificator
{
public:
    ~ILoginVerificator() {}
    virtual bool wasLoginSucces() const = 0;
};
