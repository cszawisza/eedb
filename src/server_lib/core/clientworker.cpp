#include "clientworker.h"

#include <QDebug>
#include "user.h"
#include "storage.h"

ClientWorker::ClientWorker(QObject *parent) :
    QObject(parent),
    m_cache(QSharedPointer<ClientCache>(new ClientCache() )),
    m_responseFrame( SharedResponses(new protbuf::ServerResponses )) /*,
    m_defaultProcessor(QSharedPointer<MessageHandler>(new UnknownMessageProcessor()))*/
{
    auto u = QSharedPointer<eedb::handlers::User>(new eedb::handlers::User());
    auto s = QSharedPointer<eedb::handlers::Inventory>( new eedb::handlers::Inventory() );
//    auto loginProcessor = QSharedPointer<LoginProcessor>(new LoginProcessor() );
//    loginProcessor->setClientCache(m_cache);

//    auto registerUser = QSharedPointer<UserMsgProcessor>(new UserMsgProcessor() );
//    registerUser->setClientCache(m_cache);

//    m_messageProcessors.insert(MsgType::reqLogin, loginProcessor);
//    m_messageProcessors.insert(MsgType::msgUserFullData, registerUser);
    m_msgHandlers.insert( protbuf::ClientRequest::kMsgUserReq, u );
    m_msgHandlers.insert( protbuf::ClientRequest::kMsgInventoryReq, s);
}

void ClientWorker::printMessageInfo(const protbuf::ClientRequest &request)
{
    qDebug() << "recived message id: " << request.requestid()
    << "\ntype: " << request.data_case()
//    << "\naction: " << message.action()
    << "\ndata size: " << request.ByteSize();
//    << "\nhas filters? " << message.has_filter()
//    << "\nhas limits? " << message.has_limits()
//    << "\nis_compressed? " << message.compressed()
            ;
}

void ClientWorker::processMessages()
{
    for(int msgId=0; msgId<m_inputFrame->request_size(); msgId++ ){
        printMessageInfo(m_inputFrame->request(msgId));
        auto processor = m_msgHandlers.value(m_inputFrame->request(msgId).data_case(),  QSharedPointer<MessageHandler>(new MessageHandler()));

        processor->setOutputData(m_responseFrame);
        processor->process( *m_inputFrame->mutable_request(msgId));
    }
}

void ClientWorker::processBinnaryMessage(QByteArray frame)
{
    m_responseFrame->Clear();
    RequestsDecoder decoder(frame);
    decoder.decodeTo(m_inputFrame);

    processMessages();

    QByteArray ba;
    ba.resize(m_responseFrame->ByteSize());
    m_responseFrame->SerializeToArray(ba.data(), ba.size());

    emit binnaryMessageReadyToSend(ba);
    emit jobFinished();
}
