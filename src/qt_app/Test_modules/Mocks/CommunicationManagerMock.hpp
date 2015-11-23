#pragma once

#include <gmock/gmock.h>
#include <string>
#include <ICommunicationManager.hpp>

class ICommunicationManagerMock : public ICommunicationManager
{
    Q_OBJECT
    // ICommunicationManager interface
public:
    virtual pb::ClientRequest *newRequest(uint64_t &request_id)=0;
    virtual QSharedPointer<ISocket> socket() const=0;

public slots:
    virtual void sendUserRequest(std::shared_ptr<pb::UserReq> data)=0;
};

class CommunicationManagerMock : public ICommunicationManagerMock
{
    Q_OBJECT
public:
    MOCK_METHOD1_T(newRequest, pb::ClientRequest *(uint64_t &request_id));
    MOCK_CONST_METHOD0_T(socket, QSharedPointer<ISocket> ());
    MOCK_METHOD1_T(sendUserRequest, void (std::shared_ptr<pb::UserReq> data));
};
