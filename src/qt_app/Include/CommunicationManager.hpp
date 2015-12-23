#pragma once
#include <string>

#include <ICommunicationManager.hpp>

#include "IRequestSerializer.hpp"

#include "ISocket.hpp"

class QByteArray;
class Url;


class CommunicationManager : public ICommunicationManager
{
    Q_OBJECT
public:
    CommunicationManager(QSharedPointer<ISocket> p_webSocket,
                         std::shared_ptr<IRequestsSerializer> p_serializer,
                         std::shared_ptr<IResponsesDeserializer> p_deserializer);

    //    void handleRegister(std::string &, std::string &, std::string &,
    //                        std::string &, std::string &, std::string &) ;
    ~CommunicationManager(){}

    //    pb::ClientRequest *newRequest(uint64_t &request_id ) override;

    void sendRequest();
    //    QSharedPointer<ISocket> socket() const override;
public slots:
    void sendUserRequest(std::shared_ptr<IClientRequest> data) override;
    void openConnection(const Url &url) const override;
    void closeConnection() const override;

private:
    QSharedPointer<ISocket> m_socket;
    std::shared_ptr<IRequestsSerializer> m_convertProtobufToQByteArray;
    std::shared_ptr<IResponsesDeserializer> m_convertQByteArrayToProtobuf;
    //    pb::ClientRequest p_clientRequests;
};
