#pragma once

#include "ISocket.hpp"
#include <memory>
#include <QWebSocket>

class WebSocket : public ISocket{
    Q_OBJECT
public:
    WebSocket();
    ~WebSocket() = default;
public slots:
    void sendBinaryMessage(QByteArray message) override;
    void open(const QUrl &url) override;
    void close(ISocket::CloseCode closeCode = ISocket::CloseCodeNormal, const QString & reason = QString()) override;
    QAbstractSocket::SocketState state() const;

private:
    std::unique_ptr<QWebSocket> m_socket;
};

