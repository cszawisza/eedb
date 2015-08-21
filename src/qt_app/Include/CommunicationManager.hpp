#pragma once

#include <ICommunicationManager.hpp>
#include <ProtobufConverters.hpp>

class QWebSocket;
class QByteArray;

namespace pb
{
    class ClientRequests;
}

class CommunicationManager : public ICommunicationManager
{
public:
    CommunicationManager(QWebSocket & p_webSocket,
                         ProtobufToQByteArrayConverter p_convertProtobufToString,
                         QByteArrayToProtobufConverter p_convertQByteArrayToProtobuf);
    void handle() const override;


private:
    void sendBinaryMessageOverQWebSocket(const pb::ClientRequests & p_clientRequests) const;
    QWebSocket & m_webSocket;
    ProtobufToQByteArrayConverter m_convertProtobufToQByteArray;
    QByteArrayToProtobufConverter m_convertQByteArrayToProtobuf;
};
