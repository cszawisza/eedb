#include "clientworker.h"

#include <QDebug>

#include "ProcessingUnits/UserPU.hpp"
#include "ProcessingUnits/InventoryPU.hpp"
#include "ProcessingUnits/CategoryPU.hpp"
#include "ProcessingUnits/ItemPU.hpp"

#include "utils/LogUtils.hpp"
#include "iprocessor.h"

#include <DataStructures/Adapters/Protobuf/ClientRequestAdapter.hpp>
#include <DataStructures/Adapters/Protobuf/ServerResponseAdapter.hpp>

ClientWorker::ClientWorker(QObject *parent) :
    QObject(parent),
    m_cache( std::make_shared<UserData>()),
    m_request( std::make_shared<ClientRequest>() ),
    m_response( std::make_shared<ServerResponse>() )
{
    m_msgHandlers.insert( actions::typeUser,
                          QSharedPointer<eedb::pu::UserPU>(new eedb::pu::UserPU() ));
    m_msgHandlers.insert( actions::typeCategory,
                          QSharedPointer<eedb::pu::CategoryPU>(new eedb::pu::CategoryPU()) );

//    m_msgHandlers.insert( protobuf::ClientRequest::kMsgInventoryReq, QSharedPointer<eedb::pu::InventoryPU>( new eedb::pu::InventoryPU() ));
//    m_msgHandlers.insert( protobuf::ClientRequest::kCategoryReq, QSharedPointer<eedb::pu::CategoryPU>(new eedb::pu::CategoryPU() ));
}

void ClientWorker::printMessageInfo(const IMessageContainer *request)
{
    getServerLoger()->trace("Get req message of type: {}, from user {}",
                            request->message_type().get_value_or(ActionTypeId(-1, "unknown message type")).getName(),
                            m_cache->uid() );
}

void ClientWorker::processMessage( )
{
    printMessageInfo( m_request.get() );
    auto processor = m_msgHandlers.value( m_request->message_type().get_value_or(ActionTypeId(-1, "unknown message type")),
                                          QSharedPointer<IMessageProcessingUnit>(new IMessageProcessingUnit()));
    processor->setUserData(m_cache);
    m_response->Clear();
    processor->setOutputData( m_response );
    processor->prepareNewResponse();
    m_response->set_in_response_to( m_request->get_requestId() );
    processor->process( m_request.get() );

    emit binnaryMessageReadyToSend( m_response->serialize() );
}

void ClientWorker::processBinnaryMessage(QByteArray frame)
{
    emit beforeProcessing();

    m_request->parse(frame);
    processMessage( );

    emit afterProcessing();
}
