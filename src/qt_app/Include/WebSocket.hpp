#pragma once

#include "ISocket.hpp"
#include <QWebSocket>

class WebSocket : public ISocket{
    Q_OBJECT
public:
    WebSocket(){}
    // ISocket interface
public slots:
    void sendBinaryMessage(QByteArray message) override;
    void open(const QUrl &url) override;
    void close(ISocket::CloseCode closeCode = ISocket::CloseCodeNormal, const QString & reason = QString()) override;

private:
    QWebSocket m_socket;
};

