#pragma once

class ICommunicationManager
{
public:
    virtual void handle() const = 0;
    virtual ~ICommunicationManager() {}
};
