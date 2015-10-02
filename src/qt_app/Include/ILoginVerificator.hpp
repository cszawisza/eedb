#pragma once

#include <string>

class ILoginVerificator
{
public:
    virtual bool tryLogin(const std::string &, const std::string &) const = 0;
    virtual ~ILoginVerificator() {}
};
