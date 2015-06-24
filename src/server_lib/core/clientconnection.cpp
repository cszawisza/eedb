#include "clientconnection.h"

ClientConnection::ClientConnection(QWebSocket *socket, QObject *parent) :
     QObject(parent),m_socket(socket), m_workerThread(new QThread()), m_worker( new ClientWorker() )
{     
    connect(m_workerThread, SIGNAL(finished()),
            m_workerThread, SLOT(deleteLater()));

    // socket disconnected
    connect(m_socket, &QWebSocket::disconnected, [=](){
        emit disconnected();
    });

    // when a frame can be send to client
    connect(m_worker, SIGNAL(binnaryMessageReadyToSend(QByteArray)), this, SLOT(sendData(QByteArray)));

    // increment recived data size
    connect(m_socket, &QWebSocket::binaryMessageReceived, [&](const QByteArray &frame){
        timer.restart();
        m_bytesRecived += frame.size();
    });

    // frame recived can be passed to worker thread
    connect(m_socket, SIGNAL(binaryMessageReceived(QByteArray)),
            m_worker, SLOT(processBinnaryMessage(QByteArray)), Qt::QueuedConnection);

    connect(m_socket, &QWebSocket::disconnected, [&](){
        emit disconnected();
        ///TODO save all panding values in database (last group, item etc)
    });

    m_worker->moveToThread(m_workerThread);
    m_workerThread->start();
}

void ClientConnection::sendData(QByteArray ba){
    m_bytesSend += ba.size();
    auto sent = m_socket->sendBinaryMessage(ba);
    qDebug() << "request served in: " << timer.nsecsElapsed() / 1000.0 << " µs";
    qDebug() << "send: " << sent << " Bytes";
//        qDebug() << "Message sent: " << frame.toHex();
}

ClientConnection::~ClientConnection()
{
    m_workerThread->quit();
    m_socket->deleteLater();
    m_worker->deleteLater();
}
