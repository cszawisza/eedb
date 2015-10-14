#pragma once

#include <string>

class ICommunicationManager
{
public:
    virtual void handle() const = 0;
    virtual void handleRegister(std::string &, std::string &, std::string &,
                                std::string &, std::string &, std::string &) const = 0;
    virtual ~ICommunicationManager() {}
};
