#pragma once

#include <gmock/gmock.h>
#include <string>
#include <ICommunicationManager.hpp>
#include "utils/Url.hpp"

class ICommunicationManagerMock : public ICommunicationManager
{
    Q_OBJECT
    // ICommunicationManager interface
public:
//    virtual pb::ClientRequest *newRequest(uint64_t &request_id)=0;
public slots:
    virtual void openConnection( const Url &url) const=0;
    virtual void closeConnection()const=0;
    virtual void sendUserRequest( IClientRequest* data)=0;
};


class CommunicationManagerMock : public ICommunicationManagerMock
{
    Q_OBJECT
public:
//    MOCK_METHOD1_T(newRequest, pb::ClientRequest *(uint64_t &request_id));
    MOCK_METHOD1_T(sendUserRequest, void (IClientRequest* data));
    MOCK_CONST_METHOD1_T(openConnection, void(const Url&));
    MOCK_CONST_METHOD0_T(closeConnection, void ());
};
