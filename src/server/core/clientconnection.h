#pragma once

#include <QObject>
#include <QWebSocket>
#include <QThread>
#include <QElapsedTimer>

#include "clientworker.h"

/**
 * @brief The ClientConnection class
 * Thic class represents connected client it manages data reciwe/send
 */
class ClientConnection : public QObject
{
    Q_OBJECT
public:
    explicit ClientConnection(QWebSocket *socket, QObject *parent = 0);
    ~ClientConnection();

signals:
    void disconnected();
public slots:

    void sendData(QByteArray db);
private:
    // socket can't be passed to other thread!
    QWebSocket *m_socket;
    QThread *m_workerThread;
    ClientWorker *m_worker;

    QElapsedTimer timer;

    //only statistics, can be removed later
    uint64_t m_bytesRecived = 0;
    uint64_t m_bytesSend = 0;
signals:

private slots:

};

