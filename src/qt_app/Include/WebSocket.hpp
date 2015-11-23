#pragma once

#include "ISocket.hpp"
#include <QWebSocket>

class WebSocket : public ISocket{
    Q_OBJECT
public:
    WebSocket(){
        connect(&m_socket, &QWebSocket::connected, [this](){
            emit opened();
        });

        connect(&m_socket, &QWebSocket::stateChanged, [this]( QAbstractSocket::SocketState state ){
            emit stateChanged(state);
            switch (state) {
            case QAbstractSocket::UnconnectedState:
                emit closed();
                break;
            default:
                break;
            }
        });

        connect(&m_socket, &QWebSocket::binaryMessageReceived, [this](const QByteArray &message){
           emit binaryMessageReceived(message);
        });

        connect(&m_socket, static_cast<void (QWebSocket::*)(QAbstractSocket::SocketError)>(&QWebSocket::error), [this]( QAbstractSocket::SocketError e ){
            emit error(e);
        });

    }
    // ISocket interface
public slots:
    void sendBinaryMessage(QByteArray message) override;
    void open(const QUrl &url) override;
    void close(ISocket::CloseCode closeCode = ISocket::CloseCodeNormal, const QString & reason = QString()) override;
    QAbstractSocket::SocketState state() const;

private:
    QWebSocket m_socket;
};

