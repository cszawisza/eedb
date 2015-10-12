#include "clientworker.h"

#include <QDebug>

#include "user.h"
#include "inventory.hpp"
#include "category.hpp"
#include "ItemHandler.hpp"

#include "utils/LogUtils.hpp"

ClientWorker::ClientWorker(QObject *parent) :
    QObject(parent),
    m_cache( SharedUserData (new UserData() )),
    m_responseFrame( SharedResponses(new pb::ServerResponses )) /*,
    m_defaultProcessor(QSharedPointer<MessageHandler>(new UnknownMessageProcessor()))*/
{
    m_inputFrame = SharedRequests(new pb::ClientRequests );
    m_responseFrame = SharedResponses( new pb::ServerResponses );

    m_msgHandlers.insert( pb::ClientRequest::kItemReq, QSharedPointer<eedb::handlers::ItemProcessor>(new eedb::handlers::ItemProcessor() ));
    m_msgHandlers.insert( pb::ClientRequest::kUserReq, QSharedPointer<eedb::handlers::User>(new eedb::handlers::User()) );
    m_msgHandlers.insert( pb::ClientRequest::kMsgInventoryReq, QSharedPointer<eedb::handlers::Inventory>( new eedb::handlers::Inventory() ));
    m_msgHandlers.insert( pb::ClientRequest::kCategoryReq, QSharedPointer<eedb::handlers::Category>(new eedb::handlers::Category() ));
}

void ClientWorker::printMessageInfo(const pb::ClientRequest &request)
{
    getServerLoger()->trace("Get req message(type_id:{}) from user {}", request.data_case(), m_cache->id() );
}

void ClientWorker::processMessages()
{
    for(int msgId=0; msgId<m_inputFrame->request_size(); msgId++ ){
        printMessageInfo(m_inputFrame->request(msgId));
        auto processor = m_msgHandlers.value(m_inputFrame->request(msgId).data_case(),  QSharedPointer<MessageHandler>(new MessageHandler()));
        processor->setUserData(m_cache);
        processor->setInputData(m_inputFrame);
        processor->setOutputData(m_responseFrame);
        processor->process( msgId );
    }
}

void ClientWorker::processBinnaryMessage(QByteArray frame)
{
    m_responseFrame->Clear();
    RequestsDecoder decoder(frame);
    decoder.decodeTo(*m_inputFrame);

    processMessages();

    QByteArray ba;
    ba.resize(m_responseFrame->ByteSize());
    m_responseFrame->SerializeToArray(ba.data(), ba.size());

    emit binnaryMessageReadyToSend(ba);
    emit jobFinished();
}
