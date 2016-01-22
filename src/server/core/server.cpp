#include "server.h"

#include <QWebSocket>
#include <QPointer>

#include "database/initialize.hpp"
#include "utils/LogUtils.hpp"

EEDB::EEDB(QObject *parent) :
    QWebSocketServer(QStringLiteral("EKATALOG"),QWebSocketServer::NonSecureMode, parent)
{
}

void EEDB::startServer()
{
    DB db;
    eedb::DBInitialize dbinit;
    dbinit.initializeDB( db );

    quint16 port = setup.value(QStringLiteral("listenPort"), 6666).toUInt();
    if(!this->listen(QHostAddress::Any, port)){
        throw std::runtime_error("Can't listen on port: " + std::to_string(port));
    }

     connect(this, SIGNAL(newConnection()), this, SLOT(incomingConnection()));
     connect(this, SIGNAL(acceptError(QAbstractSocket::SocketError)), this, SLOT(processConnectionError(QAbstractSocket::SocketError)));
}

void EEDB::processConnectionError(QAbstractSocket::SocketError e)
{
    qDebug() << "connetion error :" << e;
}

void EEDB::incomingConnection()
{
    while(hasPendingConnections()){
        QWebSocket *ws = nextPendingConnection();
        getServerLoger()->info( "{}, state changed to: {}", ws->peerAddress().toString(), QAbstractSocket::ConnectedState );
        ClientConnection *connection = new ClientConnection(ws);
        m_connectedClients.append(connection);
        connect(connection, SIGNAL(disconnected()),
                this, SLOT(removeConnection()));
    }
}

void EEDB::removeConnection()
{
    auto con = dynamic_cast<ClientConnection*>( sender() );
    m_connectedClients.removeOne( con );
    con->deleteLater();
}
