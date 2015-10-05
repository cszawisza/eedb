#include <QWebSocket>
#include <CommunicationManager.hpp>
#include "message_conteiner.pb.h"
#include <boost/optional.hpp>
#include "user.pb.h"

void handleConvertedMessage(const pb::ServerResponses & p_serverResponse)
{
    switch(p_serverResponse.response(0).data_case())
    {
    case pb::ServerResponse::kUserRes:
        break;
    case pb::ServerResponse::kMsgInventoryRes:
        break;
    case pb::ServerResponse::kItemRes:
        break;
    case pb::ServerResponse::kCategoryRes:
        break;
    case pb::ServerResponse::kMsgParameterRes:
        break;
    case pb::ServerResponse::DATA_NOT_SET:
        break;
    default:
        break;
    }
}

CommunicationManager::CommunicationManager(QWebSocket & p_webSocket,
                                           ProtobufToQByteArrayConverter p_convertProtobufToString,
                                           QByteArrayToProtobufConverter p_convertQByteArrayToProtobuf)
    : m_webSocket(p_webSocket),
      m_convertProtobufToQByteArray(p_convertProtobufToString),
      m_convertQByteArrayToProtobuf(p_convertQByteArrayToProtobuf)
{ }

void CommunicationManager::handle() const
{
    QObject::connect(&m_webSocket, &QWebSocket::binaryMessageReceived, [=](const QByteArray & p_serverResponse)
    {
        qDebug() << "Binary message recceived";
        auto l_serverResponseArray = m_convertQByteArrayToProtobuf(p_serverResponse);
        if (l_serverResponseArray)
        {
            handleConvertedMessage(l_serverResponseArray.get());
        }
    });
}

void CommunicationManager::sendBinaryMessageOverQWebSocket(const pb::ClientRequests & p_clientRequests) const
{
    m_webSocket.sendBinaryMessage(m_convertProtobufToQByteArray(p_clientRequests));
}

