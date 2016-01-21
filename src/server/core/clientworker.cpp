#include "clientworker.h"

#include <QDebug>

#include "ProcessingUnits/UserPU.hpp"
#include "ProcessingUnits/InventoryPU.hpp"
#include "ProcessingUnits/CategoryPU.hpp"
#include "ProcessingUnits/ItemPU.hpp"

#include "utils/LogUtils.hpp"
#include "iprocessor.h"

#include <DataStructures/Adapters/Protobuf/ClientRequestAdapter.hpp>

ClientWorker::ClientWorker(QObject *parent) :
    QObject(parent),
    m_cache( SharedUserData (new UserData() )),
    m_request( new ClientRequest() )
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

void ClientWorker::printMessageInfo(const IClientRequest &request)
{
    getServerLoger()->trace("Get req message(type_id:{}) from user {}", request.message_type(), m_cache->uid() );
}

void ClientWorker::processMessage( const QByteArray &message )
{
    ///FIXME
    m_request->parse(message);
    printMessageInfo( *m_request );
    auto processor = m_msgHandlers.value( m_request->message_type().get()/*,  QSharedPointer<IMessageProcessingUint>(new IMessageProcessingUint())*/);
    processor->setUserData(m_cache);
    processor->setOutputData(m_response);
    processor->process( m_request );

    emit binnaryMessageReadyToSend( m_response->serialize() );
}

void ClientWorker::processBinnaryMessage(QByteArray frame)
{
    emit beforeProcessing();
    processMessage( frame );
    emit afterProcessing();
}
