#include <QWebSocket>
#include <CommunicationManager.hpp>
#include "message_conteiner.pb.h"
#include <boost/optional.hpp>
#include "user.pb.h"

namespace
{

void handleConvertedServerResponse(const pb::ServerResponses & p_serverResponse)
{
    auto l_serverResponse = p_serverResponse.response(0);
    switch(l_serverResponse.data_case())
    {
    case pb::ServerResponse::kUserRes:
        qDebug() << "UserRes";
        break;
    case pb::ServerResponse::kMsgInventoryRes:
        qDebug() << "MsgInventoryRes";
        break;
    case pb::ServerResponse::kItemRes:
        qDebug() << "ItemRes";
        break;
    case pb::ServerResponse::kCategoryRes:
        qDebug() << "CategoryRes";
        break;
    case pb::ServerResponse::kMsgParameterRes:
        qDebug() << "MsgParameterRes";
        break;
    case pb::ServerResponse::DATA_NOT_SET:
        qDebug() << "Data not set";break;
    }
}

} // namespace anonymous

CommunicationManager::CommunicationManager(QWebSocket & p_webSocket,
                                           ProtobufToQByteArrayConverter p_convertProtobufToString,
                                           QByteArrayToProtobufConverter p_convertQByteArrayToProtobuf)
    : m_webSocket(p_webSocket),
      m_convertProtobufToQByteArray(p_convertProtobufToString),
      m_convertQByteArrayToProtobuf(p_convertQByteArrayToProtobuf)
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

void CommunicationManager::handle() const
{
    qDebug() << "CommunicationManager::handle()";
}

void CommunicationManager::handleRegister(std::string & p_userName, std::string & p_userPassword,
                                          std::string & p_userEmail,std::string & p_userAdress,
                                          std::string & p_userDescritpion, std::string & p_userPhoneNumber) const
{
    pb::ClientRequests l_mainMsg;
    qDebug() << "CommunicationManager::handleRegister()";
    auto l_request = l_mainMsg.add_request();
    {
        auto l_userreg = l_request->mutable_userreq();
        {
            auto l_add = l_userreg->mutable_add();
            {
                {
                    auto l_userBasic = l_add->mutable_basic();
                    {
                        l_userBasic->set_email(p_userEmail);
                        l_userBasic->set_name(p_userName);
                    }
                }
                l_add->set_password(p_userPassword);
            }
        }
    }
}

void CommunicationManager::sendBinaryMessageOverQWebSocket(const pb::ClientRequests & p_clientRequests) const
{
    qDebug() << "CommunicationManager::sendBinaryMessageOverQWebSocket()";
    qDebug() << m_webSocket.state();
    m_webSocket.sendBinaryMessage(m_convertProtobufToQByteArray(p_clientRequests));
}

