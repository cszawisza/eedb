#pragma once
#include <QObject>
#include <QUrl>
#include <QAbstractSocket>

class ISocket : public QObject {
    Q_OBJECT
public:
    enum CloseCode {
        CloseCodeNormal
    };
    ~ISocket() = default;

public slots:
    virtual void open(const QUrl & url) =0;
    virtual void close(ISocket::CloseCode closeCode = ISocket::CloseCodeNormal, const QString & reason = QString()) = 0;

    virtual void sendBinaryMessage(QByteArray message) = 0;
    virtual QAbstractSocket::SocketState state() const = 0;
signals:
    void stateChanged(QAbstractSocket::SocketState);
    void opened();
    void closed();
    void error(QAbstractSocket::SocketError error);

    void binaryMessageReceived(QByteArray bm);
};
