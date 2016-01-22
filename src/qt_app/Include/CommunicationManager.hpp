#pragma once
#include <string>
#include <memory>
#include <ICommunicationManager.hpp>

#include "Interfaces/ClientRequest.hpp"
#include "Interfaces/ServerResponse.hpp"

#include "ISocket.hpp"

class QByteArray;
class Url;

class CommunicationManager : public ICommunicationManager
{
    Q_OBJECT
public:
    CommunicationManager(QSharedPointer<ISocket> p_webSocket);

    ~CommunicationManager(){}

    //    protobuf::ClientRequest *newRequest(uint64_t &request_id ) override;

    void sendRequest( IClientRequest *req );
    //    QSharedPointer<ISocket> socket() const override;
public slots:
    void sendUserRequest( IClientRequest* data) override;
    void openConnection(const Url &url) const override;
    void closeConnection() const override;

private:
    QSharedPointer<ISocket> m_socket;

    std::shared_ptr<IClientRequest> m_req;
    std::shared_ptr<IServerResponse> m_res;
};
