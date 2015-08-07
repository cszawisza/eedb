#include "clientworker.h"

#include <QDebug>
#include "user.h"
#include "inventory.hpp"

ClientWorker::ClientWorker(QObject *parent) :
    QObject(parent),
    m_cache( SharedUserData (new UserData() )),
    m_responseFrame( SharedResponses(new pb::ServerResponses )) /*,
    m_defaultProcessor(QSharedPointer<MessageHandler>(new UnknownMessageProcessor()))*/
{
    m_msgHandlers.insert( pb::ClientRequest::kMsgUserReq, QSharedPointer<eedb::handlers::User>(new eedb::handlers::User()) );
    m_msgHandlers.insert( pb::ClientRequest::kMsgInventoryReq, QSharedPointer<eedb::handlers::Inventory>( new eedb::handlers::Inventory() ));
}

void ClientWorker::printMessageInfo(const pb::ClientRequest &request)
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
        processor->setInputData(m_inputFrame);
        processor->setOutputData(m_responseFrame);
        processor->process( msgId );
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
