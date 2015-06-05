#ifndef MESSAHEHANDLER_H
#define MESSAHEHANDLER_H

#include <QObject>
#include <QWebSocket>

#include "types.pb.h"
#include "messages/messagescontainer.h"

class MessaheHandler : public QObject
{
    Q_OBJECT
public:
    explicit MessaheHandler(QObject *parent = 0);

    QWebSocket *getSocket() const;
    void setSocket(QWebSocket *value);

    template<class baseClass>
    void queryMessage(baseClass *msg){
        outputMessage.addMessage(msg);
    }

signals:
    void recived_resAddParameter(QByteArray message);
    void recived_resParameters(QByteArray message);

public slots:
    void queryMessage(MsgType type, QByteArray data);
    void sendPandingMessages();
    void sendBinaryMessage(MsgType type, QByteArray ba);
    void messageRecived(QByteArray ba);
private:
    quint64 bytesSend=0;
    quint64 bytesRecived = 0;

    MessagesContainer outputMessage;
    QWebSocket *socket;
};


#endif // MESSAHEHANDLER_H
