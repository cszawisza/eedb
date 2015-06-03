#include "clientworker.h"
//#include "loginprocessor.h"
//#include "usermsgprocessor.h"

#include <QDebug>

ClientWorker::ClientWorker(QObject *parent) :
    QObject(parent),
    m_cache(QSharedPointer<ClientCache>(new ClientCache() )),
    m_defaultProcessor(QSharedPointer<IProcessor>(new UnknownMessageProcessor()))
{
//    auto loginProcessor = QSharedPointer<LoginProcessor>(new LoginProcessor() );
//    loginProcessor->setClientCache(m_cache);

//    auto registerUser = QSharedPointer<UserMsgProcessor>(new UserMsgProcessor() );
//    registerUser->setClientCache(m_cache);

//    m_messageProcessors.insert(MsgType::reqLogin, loginProcessor);
//    m_messageProcessors.insert(MsgType::msgUserFullData, registerUser);
}

void ClientWorker::printMessageInfo(const protbuf::MessageCapsule &message)
{
    qDebug() << "recived message id: " << message.msgid()
    << "\ntype: " << message.msgtype()
    << "\naction: " << message.action()
    << "\ndata size: " << message.data().size()
    << "\nhas filters? " << message.has_filter()
    << "\nhas limits? " << message.has_limits()
    << "\nis_compressed? " << message.compressed();
}

void ClientWorker::processData()
{
    auto message = m_frameParser.nextPandingMessage();
    auto processor = m_messageProcessors.value(message.msgtype(), m_defaultProcessor);
    auto id = message.msgid();

    printMessageInfo(message);
    processor->setWorkingCapsule(message);
    if ( processor->checkUserState() ){ // check if user state is apriopriet (is logged)
        if (!processor->preProcess())
            emit messageCorrupted( message.msgid() ); // no emit, resend message to client?
        else{
            processor->process();
            auto response = processor->generateResponse();
            for (int i=0;i<response.size();i++){
                auto capsule = response[i];
                capsule.set_msgid(id);
                if( !capsule.has_msgtype() )
                    capsule.set_msgtype( MsgType::dummyResponse );
                m_responseFrame.add_capsules()->CopyFrom(capsule);
            }
        }
    }
}

void ClientWorker::processBinnaryMessage(const QByteArray frame)
{
    m_responseFrame.Clear();
    m_frameParser.prepareMessages(frame);

    while (m_frameParser.hasPandingMessags() )
        processData();

    QByteArray ba;
    ba.resize(m_responseFrame.ByteSize());
    m_responseFrame.SerializeToArray(ba.data(), ba.size());

    emit binnaryMessageReadyToSend(ba);
    emit jobFinished();
}
