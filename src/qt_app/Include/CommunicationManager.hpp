#pragma once
#include <string>

#include <ICommunicationManager.hpp>

#include "IRequestsDeserializer.hpp"
#include "IResponseDeserializer.hpp"

#include "ISocket.hpp"

class QByteArray;
class Url;


class CommunicationManager : public ICommunicationManager
{
    Q_OBJECT
public:
    CommunicationManager(QSharedPointer<ISocket> p_webSocket,
                         std::shared_ptr<data::IRequestsSerializer> p_serializer,
                         std::shared_ptr<data::IResponsesDeserializer> p_deserializer);

    //    void handleRegister(std::string &, std::string &, std::string &,
    //                        std::string &, std::string &, std::string &) ;
    ~CommunicationManager(){}

    //    pb::ClientRequest *newRequest(uint64_t &request_id ) override;

    void sendRequest();
    //    QSharedPointer<ISocket> socket() const override;
public slots:
    void sendUserRequest(std::shared_ptr<data::IClientRequest> data) override;
    void openConnection(const Url &url) const override;
    void closeConnection() const override;

private:
    QSharedPointer<ISocket> m_socket;
    std::shared_ptr<data::IRequestsSerializer> m_convertProtobufToQByteArray;
    std::shared_ptr<data::IResponsesDeserializer> m_convertQByteArrayToProtobuf;
    //    pb::ClientRequest p_clientRequests;
};
