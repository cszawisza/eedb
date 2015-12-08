#pragma once
#include <string>

#include <ICommunicationManager.hpp>
#include <ProtobufConverters.hpp>
#include "ISocket.hpp"

class QByteArray;
class Url;


class CommunicationManager : public ICommunicationManager
{
    Q_OBJECT
public:
    CommunicationManager(QSharedPointer<ISocket> p_webSocket,
                         ProtobufToQByteArrayConverter p_convertProtobufToString,
                         QByteArrayToProtobufConverter p_convertQByteArrayToProtobuf);

//    void handleRegister(std::string &, std::string &, std::string &,
//                        std::string &, std::string &, std::string &) ;
    ~CommunicationManager(){}

    pb::ClientRequest *newRequest(uint64_t &request_id ) override;

    void sendRequest();
//    QSharedPointer<ISocket> socket() const override;
public slots:
    void sendUserRequest(std::shared_ptr<pb::UserReq> data) override;
    void openConnection(const Url &url) const override;
    void closeConnection() const override;

private:
    QSharedPointer<ISocket> m_socket;
    ProtobufToQByteArrayConverter m_convertProtobufToQByteArray;
    QByteArrayToProtobufConverter m_convertQByteArrayToProtobuf;
    pb::ClientRequest p_clientRequests;
};
