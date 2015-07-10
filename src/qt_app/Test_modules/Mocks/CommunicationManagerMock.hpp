#pragma once

#include <ICommunicationManager.hpp>
#include <CommunicationManager.hpp>

class CommunicationManagerMock : public ICommunicationManager
{
public:
    MOCK_METHOD0(handle, void());
};
