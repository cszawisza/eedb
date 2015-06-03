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
    connect(m_worker, &ClientWorker::binnaryMessageReadyToSend, [=](const QByteArray &frame){
        m_bytesSend += frame.size();
        m_socket->sendBinaryMessage(frame); ///TODO check socket state?
        qDebug() << "request served in: " << timer.nsecsElapsed() / 1000.0 << " µs";
        ///NOTE provide feedback to worker, about frame send data state
    });


    // increment recived data size
    connect(m_socket, &QWebSocket::binaryMessageReceived, [=](const QByteArray &frame){
        timer.restart();
        m_bytesRecived += frame.size();
    });

    // frame recived can be passed to worker thread
    connect(m_socket, SIGNAL(binaryMessageReceived(QByteArray)),
            m_worker, SLOT(processBinnaryMessage(QByteArray)), Qt::QueuedConnection);

    m_worker->moveToThread(m_workerThread);
    m_workerThread->start();
}

ClientConnection::~ClientConnection()
{
    m_socket->deleteLater();
    m_worker->deleteLater();
}
