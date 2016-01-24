#pragma once

#include <gmock/gmock.h>
#include <string>
#include <ICommunicationManager.hpp>
#include "utils/Url.hpp"

class ICommunicationManagerMock : public IUserCommunicationManager
{
    Q_OBJECT
    // ICommunicationManager interface
public:
    virtual IClientRequest* newRequest() = 0;
    virtual void sendRequest( ) = 0;
public slots:
    virtual void openConnection( const Url &url) const=0;
    virtual void closeConnection()const=0;
};


class CommunicationManagerMock : public ICommunicationManagerMock
{
    Q_OBJECT
public:
    MOCK_METHOD0_T(newRequest, IClientRequest*() );
    MOCK_METHOD0_T(sendRequest, void ( ) );
    MOCK_CONST_METHOD1_T(openConnection, void(const Url&));
    MOCK_CONST_METHOD0_T(closeConnection, void ());
};
