#pragma once

//#include "ICommunicationManager.hpp"
#include <ICommunicationManager.hpp>

class CommunicationManager : public ICommunicationManager
{
public:
    CommunicationManager();
    void handle() override;
};
