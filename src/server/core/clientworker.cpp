#include "clientworker.h"

#include <QDebug>

#include "ProcessingUnits/UserPU.hpp"
#include "ProcessingUnits/InventoryPU.hpp"
#include "ProcessingUnits/CategoryPU.hpp"
#include "ProcessingUnits/ItemPU.hpp"

#include "utils/LogUtils.hpp"

ClientWorker::ClientWorker(QObject *parent) :
    QObject(parent),
    m_cache( SharedUserData (new UserData() ))
//    m_responseFrame( SharedResponses(new protobuf::ServerResponses ))
  /*,
    m_defaultProcessor(QSharedPointer<MessageHandler>(new UnknownMessageProcessor()))*/
{
//    m_inputFrame = SharedRequests(new protobuf::ClientRequests );
//    m_responseFrame = SharedResponses( new protobuf::ServerResponses );
///FIXME
//    m_msgHandlers.insert( protobuf::ClientRequest::kItemReq, QSharedPointer<eedb::pu::ItemPU>(new eedb::pu::ItemPU() ));
//    m_msgHandlers.insert( protobuf::ClientRequest::kUserReq, QSharedPointer<eedb::pu::UserPU>(new eedb::pu::UserPU()) );
//    m_msgHandlers.insert( protobuf::ClientRequest::kMsgInventoryReq, QSharedPointer<eedb::pu::InventoryPU>( new eedb::pu::InventoryPU() ));
//    m_msgHandlers.insert( protobuf::ClientRequest::kCategoryReq, QSharedPointer<eedb::pu::CategoryPU>(new eedb::pu::CategoryPU() ));
}

void ClientWorker::printMessageInfo(const protobuf::ClientRequest &request)
{
    getServerLoger()->trace("Get req message(type_id:{}) from user {}", request.data_case(), m_cache->id() );
}

void ClientWorker::processMessages()
{
    ///FIXME
//    for(int msgId=0; msgId<m_inputFrame->request_size(); msgId++ ){
//        printMessageInfo(m_inputFrame->request(msgId));
//        auto processor = m_msgHandlers.value(m_inputFrame->request(msgId).data_case(),  QSharedPointer<IMessageProcessingUint>(new IMessageProcessingUint()));
//        processor->setUserData(m_cache);
//        processor->setInputData(m_inputFrame);
//        processor->setOutputData(m_responseFrame);
//        processor->process( msgId );
//    }
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
