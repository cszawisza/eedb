#include "WebSocket.hpp"


void WebSocket::sendBinaryMessage(QByteArray message)
{
    m_socket.sendBinaryMessage(message);
}

void WebSocket::open(const QUrl &url)
{
    QUrl cUrl = url;
    cUrl.setScheme("ws");
    m_socket.open(cUrl);
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

    m_socket.close(code, reason);
}

QAbstractSocket::SocketState WebSocket::state() const
{
    return m_socket.state();
}
