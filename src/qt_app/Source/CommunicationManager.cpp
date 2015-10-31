#include <QWebSocket>
#include <CommunicationManager.hpp>
#include "message_conteiner.pb.h"
#include <boost/optional.hpp>
#include "user.pb.h"

namespace
{

void handleConvertedServerResponse(const pb::ServerResponses & p_serverResponse)
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

} // namespace anonymous

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
            handleConvertedServerResponse(l_serverResponseArray.get());
        }
    });
}

void CommunicationManager::handleRegister(std::string & p_userName, std::string & p_userPassword,
                                          std::string & p_userEmail,std::string & p_userAdress,
                                          std::string & p_userDescritpion, std::string & p_userPhoneNumber) const
{
    pb::ClientRequests l_mainMsg;
    qDebug() << "handleRegister()";
    auto l_request = l_mainMsg.add_request();
    {
        auto l_userreg = l_request->mutable_userreq();
        {
            auto l_login = l_userreg->mutable_login();
            {
                {
                    auto l_cred = l_login->mutable_cred();
                    {
                        l_cred->set_name(p_userName);
                    }
                }
                l_login->set_password(p_userPassword);
            }
        }
    }
    qDebug() << QString::fromStdString(p_userName);
    qDebug() << QString::fromStdString(p_userPassword);
    sendBinaryMessageOverQWebSocket(l_mainMsg);
}

void CommunicationManager::sendBinaryMessageOverQWebSocket(const pb::ClientRequests & p_clientRequests) const
{
    qDebug() << "sendBinaryMessageOverQWebSocket()";
    m_webSocket.sendBinaryMessage(m_convertProtobufToQByteArray(p_clientRequests));
}

