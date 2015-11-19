#pragma once

#include <gmock/gmock.h>
#include <ISocket.hpp>

class ISocketMock : public ISocket{
    Q_OBJECT
public:
    // ISocket interface
public slots:
    void sendBinaryMessage(QByteArray message) = 0;
    void open(const QUrl &url) = 0;
    void close(ISocket::CloseCode closeCode, const QString &reason) = 0;
};

class SocketMock : public ISocketMock
{
    Q_OBJECT
public:
  MOCK_METHOD1(sendBinaryMessage, void(QByteArray ba));
  MOCK_METHOD1(open, void (const QUrl &url));
  MOCK_METHOD2_T(close, void (ISocket::CloseCode closeCode, const QString &reason));
};


