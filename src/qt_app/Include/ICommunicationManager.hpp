#pragma once

class ICommunicationManager
{
public:
    virtual ~ICommunicationManager() {}
    virtual void handle() = 0;
};
