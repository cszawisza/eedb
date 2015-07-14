#pragma once

#include <ICommunicationManager.hpp>

class CommunicationManagerMock : public ICommunicationManager
{
public:
    MOCK_CONST_METHOD0(handle, void());
};
