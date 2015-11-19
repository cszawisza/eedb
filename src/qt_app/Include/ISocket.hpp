#pragma once
#include <QUrl>
#include <QObject>

class ISocket : public QObject {
    Q_OBJECT

public:
    enum CloseCode {
        CloseCodeNormal
    };

    ISocket(){}

public slots:
    virtual void open(const QUrl & url) =0;
    virtual void close(ISocket::CloseCode closeCode = ISocket::CloseCodeNormal, const QString & reason = QString()) = 0;

    virtual void sendBinaryMessage(QByteArray message) = 0;

signals:
    void binaryMessageReceived(QByteArray bm);
    void connected();
};
