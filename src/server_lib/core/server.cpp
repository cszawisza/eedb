#include "server.h"

#include <QWebSocket>
#include <QPointer>

QCatalogServer::QCatalogServer(QObject *parent) :
    QWebSocketServer(QStringLiteral("EKATALOG"),QWebSocketServer::NonSecureMode, parent)
{
}

void QCatalogServer::startServer()
{
    quint16 port = setup.value("listenPort", 6666).toUInt();
    if(!this->listen(QHostAddress::Any, port)){
        throw std::runtime_error("Can't listen on port: " + std::to_string(port));
    }

     connect(this, SIGNAL(newConnection()), this, SLOT(incomingConnection()));
     connect(this, SIGNAL(acceptError(QAbstractSocket::SocketError)), this, SLOT(processConnectionError(QAbstractSocket::SocketError)));
}

void QCatalogServer::processConnectionError(QAbstractSocket::SocketError e)
{
    qDebug() << "connetion error :" << e;
}


void QCatalogServer::incomingConnection()
{
    while(hasPendingConnections()){
        QWebSocket *ws = nextPendingConnection();

        auto connection = new ClientConnection(ws);
        m_connectedClients.append(connection);
//        if (thread){
//            connect(thread, SIGNAL(finished()),
//                    this, SLOT(collectDeadThread()));

//            connect(ws, SIGNAL(binaryMessageReceived(QByteArray)),
//                    thread, SLOT(recivedBinnaryMessage(QByteArray)));

//            connect(thread, SIGNAL(sendBinaryMessage(QByteArray)),
//                    this, SLOT(send(QByteArray)));

//            connect(ws, SIGNAL(disconnected()),
//                    thread, SLOT(quit()));

//            thread->start();
//            thread->setPriority(QThread::LowestPriority);
//        }
    }
}
