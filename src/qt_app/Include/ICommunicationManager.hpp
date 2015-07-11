#pragma once

class ICommunicationManager
{
public:
    virtual ~ICommunicationManager() {}
    virtual void handle() const = 0;
};
