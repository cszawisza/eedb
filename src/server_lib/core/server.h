#pragma once
#include <QWebSocketServer>
#include <QSettings>
#include "clientconnection.h"

class QCatalogServer : public QWebSocketServer
{
    Q_OBJECT
public:
    explicit QCatalogServer(QObject *parent = 0);
    ~QCatalogServer(){;}

    void startServer();
signals:

public slots:
public:
protected:
    QSettings setup;
private slots:
    void processConnectionError(QAbstractSocket::SocketError);
    void incomingConnection();

private:
    QList<ClientConnection*> m_connectedClients;
};
