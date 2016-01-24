#include "WebSocket.hpp"

WebSocket::WebSocket():
    m_socket( std::make_unique<QWebSocket>() )
{
    connect( m_socket.get(), &QWebSocket::connected, [this](){
        emit opened();
    });

    connect( m_socket.get(), &QWebSocket::stateChanged, [this]( QAbstractSocket::SocketState state ){
        emit stateChanged(state);
        switch (state) {
        case QAbstractSocket::UnconnectedState:
            emit closed();
            break;
        default:
            break;
        }
    });

    connect( m_socket.get(), &QWebSocket::binaryMessageReceived, [this](const QByteArray &message){
        emit binaryMessageReceived(message);
    });

    connect( m_socket.get(), static_cast<void (QWebSocket::*)(QAbstractSocket::SocketError)>(&QWebSocket::error), [this]( QAbstractSocket::SocketError e ){
        emit error(e);
    });
}

void WebSocket::sendBinaryMessage(QByteArray message)
{
    m_socket->sendBinaryMessage(message);
}

void WebSocket::open(const QUrl &url)
{
    auto p_url = url;
    p_url.setScheme(QStringLiteral("ws"));
    m_socket->open(p_url);
}

void WebSocket::close(ISocket::CloseCode closeCode, const QString &reason)
{
    QWebSocketProtocol::CloseCode code;
    switch (closeCode) {
    case CloseCodeNormal:
        code = QWebSocketProtocol::CloseCodeNormal;
        break;
    default:
        break;
    }
    //        CloseCodeNormal                 = 1000,
    //        CloseCodeGoingAway              = 1001,
    //        CloseCodeProtocolError          = 1002,
    //        CloseCodeDatatypeNotSupported   = 1003,
    //        CloseCodeReserved1004           = 1004,
    //        CloseCodeMissingStatusCode      = 1005,
    //        CloseCodeAbnormalDisconnection  = 1006,
    //        CloseCodeWrongDatatype          = 1007,
    //        CloseCodePolicyViolated         = 1008,
    //        CloseCodeTooMuchData            = 1009,
    //        CloseCodeMissingExtension       = 1010,
    //        CloseCodeBadOperation           = 1011,
    //        CloseCodeTlsHandshakeFailed     = 1015
    //    };

    m_socket->close(code, reason);
}

QAbstractSocket::SocketState WebSocket::state() const
{
    return m_socket->state();
}
