#pragma once

#include <string>

#include <ICommunicationManager.hpp>
#include <ProtobufConverters.hpp>
#include "ISocket.hpp"

class QByteArray;

namespace pb
{
    class ClientRequests;
}

class CommunicationManager : public ICommunicationManager
{
    Q_OBJECT
public:
    CommunicationManager(QSharedPointer<ISocket> p_webSocket,
                         ProtobufToQByteArrayConverter p_convertProtobufToString,
                         QByteArrayToProtobufConverter p_convertQByteArrayToProtobuf);


    void handleRegister(std::string &, std::string &, std::string &,
                        std::string &, std::string &, std::string &) ;
    ~CommunicationManager(){}
private:
    QSharedPointer<ISocket> m_socket;
    ProtobufToQByteArrayConverter m_convertProtobufToQByteArray;
    QByteArrayToProtobufConverter m_convertQByteArrayToProtobuf;

    // ICommunicationManager interface
public:
    pb::ClientRequest *newRequest(uint64_t &request_id );

    void sendRequest();
public slots:
    void sendUserRequest(std::shared_ptr<pb::UserRes> data);

private:
    pb::ClientRequests p_clientRequests;
};
