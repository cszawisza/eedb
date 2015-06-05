#include "messahehandler.h"

#include <QDebug>
#include "messages/messagescontainer.h"

MessaheHandler::MessaheHandler(QObject *parent) :
    QObject(parent)
{
}
QWebSocket *MessaheHandler::getSocket() const{
    return socket;
}

void MessaheHandler::setSocket(QWebSocket *value){
    socket = value;
    connect(socket, SIGNAL(binaryMessageReceived(QByteArray)),SLOT(messageRecived(QByteArray)));
}

void MessaheHandler::messageRecived(QByteArray ba){
    bytesRecived += ba.size();

    MessagesContainer mc;
    mc.fromArray(ba);
    qDebug()<< mc.getCapsule(0).msgtype() << mc.capsules().size();
    for(int i=0;i<mc.capsules_size();i++){
        if(mc.getCapsule(i).msgtype() == MsgType::resAddParameter ){
            emit recived_resAddParameter( mc.getCapsule(i).getData() );
        }
        else if(mc.getCapsule(i).msgtype() == MsgType::resParameters ){
            emit recived_resParameters( mc.getCapsule(i).getData() );
        }
    }
}

void MessaheHandler::queryMessage(MsgType type, QByteArray data){
    outputMessage.addMessage(type,data);
}

void MessaheHandler::sendBinaryMessage(MsgType type, QByteArray ba){
    outputMessage.addMessage(type,ba);
    sendPandingMessages();
}

void MessaheHandler::sendPandingMessages(){
    if(outputMessage.capsules().size() > 0){
        bytesSend += socket->sendBinaryMessage(outputMessage.toArray());
        outputMessage.Clear();
    }
}
