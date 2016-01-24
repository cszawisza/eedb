#include "CommunicationManager.hpp"
#include "ISocket.hpp"

#include <boost/optional.hpp>
#include "utils/Url.hpp"

#include <DataStructures/StructuresCommon.hpp>
#include <DataStructures/Interfaces/DefinedActions.hpp>

///TODO create a factory to remove adapter dependency from this file
#include <DataStructures/Adapters/Protobuf/ServerResponseAdapter.hpp>
#include <DataStructures/Adapters/Protobuf/ClientRequestAdapter.hpp>

CommunicationManager::CommunicationManager(QSharedPointer<ISocket> p_webSocket)
    : m_socket(p_webSocket),
      m_response(std::make_shared<ServerResponse>() ),
      m_request(std::make_shared<ClientRequest>() )
{
    auto socket = m_socket.data();

    QObject::connect(socket, &ISocket::binaryMessageReceived, [=](const QByteArray & p_serverResponse)
    {
        qDebug() << "Binary message recceived";
        m_response->Clear();

        try{
            m_response->parse(p_serverResponse);
            if(m_response->message_type().is_initialized()){
                qDebug() << "" << m_response->message_type().get().getName();

                if( m_response->response_code() == IServerResponse::NoError ){
                    switch ( m_response->message_type().get() ) {
                    case actions::typeUser:
                        emit receivedMessage( m_response->get_user() );
                        break;
                    case actions::typeCategory:
                        emit receivedMessage( m_response->get_category() );
                        break;
//                    case actions::typeItem:
//                        emit receivedMessage( );
                    default:
                        break;
                    }
                }
                else{
                    ///TODO has ERROR Code, do something?
                    qDebug() << "Has error!!";
                }
            }
            else{
                ///TODO data not initialized, do something
                qDebug() << "Has bad data!!";
            }
        }
        catch( ... ){
            ///TODO log false data
        }
    });

    QObject::connect(socket, &ISocket::opened, [this](){
       emit socketConnected();
    });

    QObject::connect(socket, &ISocket::closed, [this](){
        emit socketDisconnected();
    });
}

IClientRequest *CommunicationManager::newRequest()
{
    return m_request.get();
}

void CommunicationManager::sendRequest()
{
    if(m_socket->state() == QAbstractSocket::ConnectedState ){
//        qDebug() << "CommunicationManager::sendBinaryMessageOverQWebSocket()";
        m_socket->sendBinaryMessage( m_request->serialize() );
    }
}

void CommunicationManager::openConnection(const Url &url) const
{
    m_socket->open(url);
}

void CommunicationManager::closeConnection() const
{
    auto state = m_socket->state();
    if( state == QAbstractSocket::ConnectedState || state == QAbstractSocket::ConnectingState )
        m_socket->close();

    emit socketDisconnected();
}


