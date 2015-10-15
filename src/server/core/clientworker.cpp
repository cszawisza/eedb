#include "clientworker.h"

#include <QDebug>

#include "user.h"
#include "inventory.hpp"
#include "CategoryPU.hpp"
#include "ItemPU.hpp"

#include "utils/LogUtils.hpp"

ClientWorker::ClientWorker(QObject *parent) :
    QObject(parent),
    m_cache( SharedUserData (new UserData() )),
    m_responseFrame( SharedResponses(new pb::ServerResponses )) /*,
    m_defaultProcessor(QSharedPointer<MessageHandler>(new UnknownMessageProcessor()))*/
{
    m_inputFrame = SharedRequests(new pb::ClientRequests );
    m_responseFrame = SharedResponses( new pb::ServerResponses );

    m_msgHandlers.insert( pb::ClientRequest::kItemReq, QSharedPointer<eedb::pu::ItemPU>(new eedb::pu::ItemPU() ));
    m_msgHandlers.insert( pb::ClientRequest::kUserReq, QSharedPointer<eedb::pu::UserPU>(new eedb::pu::UserPU()) );
    m_msgHandlers.insert( pb::ClientRequest::kMsgInventoryReq, QSharedPointer<eedb::pu::Inventory>( new eedb::pu::Inventory() ));
    m_msgHandlers.insert( pb::ClientRequest::kCategoryReq, QSharedPointer<eedb::pu::CategoryPU>(new eedb::pu::CategoryPU() ));
}

void ClientWorker::printMessageInfo(const pb::ClientRequest &request)
{
    getServerLoger()->trace("Get req message(type_id:{}) from user {}", request.data_case(), m_cache->id() );
}

void ClientWorker::processMessages()
{
    for(int msgId=0; msgId<m_inputFrame->request_size(); msgId++ ){
        printMessageInfo(m_inputFrame->request(msgId));
        auto processor = m_msgHandlers.value(m_inputFrame->request(msgId).data_case(),  QSharedPointer<IMessageProcessingUint>(new IMessageProcessingUint()));
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
