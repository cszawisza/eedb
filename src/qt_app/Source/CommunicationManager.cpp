#include <QWebSocket>
#include "ISocket.hpp"
#include <CommunicationManager.hpp>
#include "message_conteiner.pb.h"
#include <boost/optional.hpp>
#include "user.pb.h"
#include "utils/Url.hpp"

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
        qDebug() << "Data not set";
        break;
    }
}

} // namespace anonymous

CommunicationManager::CommunicationManager(QSharedPointer<ISocket> p_webSocket,
                                           ProtobufToQByteArrayConverter p_convertProtobufToString,
                                           QByteArrayToProtobufConverter p_convertQByteArrayToProtobuf)
    : m_socket(p_webSocket),
      m_convertProtobufToQByteArray(p_convertProtobufToString),
      m_convertQByteArrayToProtobuf(p_convertQByteArrayToProtobuf)
{
    auto socket = m_socket.data();

    QObject::connect(socket, &ISocket::binaryMessageReceived, [=](const QByteArray & p_serverResponse)
    {
        qDebug() << "Binary message recceived";
        auto l_serverResponseArray = m_convertQByteArrayToProtobuf(p_serverResponse);
        if (l_serverResponseArray)
        {
            handleConvertedServerResponse(l_serverResponseArray.get());
        }
    });

    QObject::connect(socket, &ISocket::opened, [this](){
       emit socketConnected();
    });

    QObject::connect(socket, &ISocket::closed, [this](){
        emit socketDisconnected();
    });
}

//void CommunicationManager::handleRegister(std::string & p_userName, std::string & p_userPassword,
//                                          std::string & p_userEmail,std::string & p_userAdress,
//                                          std::string & p_userDescritpion, std::string & p_userPhoneNumber)
//{
////    pb::ClientRequests l_mainMsg;
//    qDebug() << "CommunicationManager::handleRegister()";
//    uint64_t id;
//    auto login = this->newRequest(id)->mutable_userreq()->mutable_add();

//    login->set_password( p_userPassword );
//    login->mutable_basic()->set_nickname(p_userName);
//    login->mutable_basic()->set_email(p_userEmail);

//    sendRequest();
//}

//void CommunicationManager::sendBinaryMessageOverQWebSocket(const pb::ClientRequests & p_clientRequests) const
//{
//
////    qDebug() << m_socket.state();
//    m_socket->sendBinaryMessage(m_convertProtobufToQByteArray(p_clientRequests));
//}

pb::ClientRequest *CommunicationManager::newRequest(uint64_t &request_id)
{
    static quint64 id = 1;
    auto req = p_clientRequests.add_request();
    req->set_request_id(id);
    request_id = id++;
    return req;
}

void CommunicationManager::sendRequest()
{
    qDebug() << "CommunicationManager::sendBinaryMessageOverQWebSocket()";
    m_socket->sendBinaryMessage(m_convertProtobufToQByteArray(p_clientRequests));
    for(const auto &req :*p_clientRequests.mutable_request() )
        emit userRequestSent( RequestMetadata(req) );
}

void CommunicationManager::sendUserRequest(std::shared_ptr<pb::UserReq> data)
{
    if(m_socket->state() == QAbstractSocket::ConnectedState ){
        sendRequest();
    }
}

void CommunicationManager::openConnection(const Url &url) const
{
    m_socket->open(url);
}

void CommunicationManager::closeConnection() const
{
    if( m_socket->state() == QAbstractSocket::ConnectedState )
        m_socket->close();
}

//QSharedPointer<ISocket> CommunicationManager::socket() const
//{
//    return m_socket;
//}

