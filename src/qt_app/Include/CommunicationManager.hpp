#pragma once
#include "ICommunicationManager.hpp"
#include <string>
#include <memory>


class QByteArray;
class Url;

class IClientRequest;
class IServerResponse;

class ISocket;

class CommunicationManager : public IUserCommunicationManager
{
    Q_OBJECT
public:
    CommunicationManager(QSharedPointer<ISocket> p_webSocket);

    ~CommunicationManager() = default;

    IClientRequest *newRequest();
    void sendRequest( ) override;
public slots:

    void openConnection(const Url &url) const override;
    void closeConnection() const override;

private:
    QSharedPointer<ISocket> m_socket;
    std::shared_ptr<IServerResponse> m_response;
    std::shared_ptr<IClientRequest> m_request;
};
