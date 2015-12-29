#include <QWebSocket>
#include "ISocket.hpp"
#include <CommunicationManager.hpp>
#include <boost/optional.hpp>
#include "utils/Url.hpp"

namespace
{

void handleConvertedServerResponse(const auto p_serverResponse)
{
//    switch(p_serverResponse.data_case())
//    {
//    case protobuf::ServerResponse::kUserRes:
//        qDebug() << "UserRes";
//        break;
//    case protobuf::ServerResponse::kMsgInventoryRes:
//        qDebug() << "MsgInventoryRes";
//        break;
//    case protobuf::ServerResponse::kItemRes:
//        qDebug() << "ItemRes";
//        break;
//    case protobuf::ServerResponse::kCategoryRes:
//        qDebug() << "CategoryRes";
//        break;
//    case protobuf::ServerResponse::kMsgParameterRes:
//        qDebug() << "MsgParameterRes";
//        break;
//    case protobuf::ServerResponse::DATA_NOT_SET:
//        qDebug() << "Data not set";
//        break;
//    }
}

} // namespace anonymous

CommunicationManager::CommunicationManager(QSharedPointer<ISocket> p_webSocket,
                                           std::shared_ptr<IClientRequest> p_req,
                                           std::shared_ptr<IServerResponse> p_res)
    : m_socket(p_webSocket),
      m_req(p_req),
      m_res(p_res)
{
    auto socket = m_socket.data();

    QObject::connect(socket, &ISocket::binaryMessageReceived, [=](const QByteArray & p_serverResponse)
    {
        qDebug() << "Binary message recceived";
//        auto l_serverResponseArray = m_convertQByteArrayToProtobuf->parseFromByteArray(p_serverResponse);
//        if (l_serverResponseArray)
        if(true)
        {
            ///FIXME
//            handleConvertedServerResponse(l_serverResponseArray.get());
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
////    protobuf::ClientRequests l_mainMsg;
//    qDebug() << "CommunicationManager::handleRegister()";
//    uint64_t id;
//    auto login = this->newRequest(id)->mutable_userreq()->mutable_add();

//    login->set_password( p_userPassword );
//    login->mutable_basic()->set_nickname(p_userName);
//    login->mutable_basic()->set_email(p_userEmail);

//    sendRequest();
//}

//void CommunicationManager::sendBinaryMessageOverQWebSocket(const protobuf::ClientRequests & p_clientRequests) const
//{
//
////    qDebug() << m_socket.state();
//    m_socket->sendBinaryMessage(m_convertProtobufToQByteArray(p_clientRequests));
//}

//protobuf::ClientRequest *CommunicationManager::newRequest(uint64_t &request_id)
//{
//    static quint64 id = 1;
//    auto req = new protobuf::ClientRequest();
//    req->set_request_id(id);
//    request_id = id++;
//    return req;
//}


void CommunicationManager::sendRequest()
{
    qDebug() << "CommunicationManager::sendBinaryMessageOverQWebSocket()";
    ///FIXME
//    m_socket->sendBinaryMessage(m_convertProtobufToQByteArray(p_clientRequests));
//    for(const auto &req :*p_clientRequests.mutable_request() )
//        emit userRequestSent( RequestMetadata(p_clientRequests) );
}

void CommunicationManager::sendUserRequest(IClientRequest* data)
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

