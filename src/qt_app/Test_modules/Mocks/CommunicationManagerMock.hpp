#pragma once

#include <string>
#include <ICommunicationManager.hpp>

class CommunicationManagerMock : public ICommunicationManager
{
public:
    MOCK_CONST_METHOD0(handle, void());
    MOCK_CONST_METHOD2(tryLogin, bool(const std::string &, const std::string &));
};
