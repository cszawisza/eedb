#pragma once
#include <QWebSocketServer>
#include <QSettings>
#include "clientconnection.h"

class EEDB : public QWebSocketServer
{
    Q_OBJECT
public:
    explicit EEDB(QObject *parent = 0);
    ~EEDB(){;}

    void startServer();
signals:

public slots:
public:
protected:
    QSettings setup;
private slots:
    void processConnectionError(QAbstractSocket::SocketError);
    void incomingConnection();
    void removeConnection();
private:
    QList<ClientConnection*> m_connectedClients;
};
