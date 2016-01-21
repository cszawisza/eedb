#include "iprocessor.h"

#include <DataStructures/Adapters/Protobuf/ClientRequestAdapter.hpp>
#include <DataStructures/Adapters/Protobuf/ServerResponseAdapter.hpp>

std::atomic<quint64> IMessageProcessingUnit::m_response_id;


IMessageProcessingUnit::IMessageProcessingUnit():
m_response( nullptr )
{
    ///FIXME
    //    m_outputFrame = SharedResponses(new protobuf::ServerResponses );
}

void IMessageProcessingUnit::setOutputData(IServerResponse *frame){
    m_response = frame;
}

void IMessageProcessingUnit::setUserData(SharedUserData userData){
    m_userData.swap(userData);
}

void IMessageProcessingUnit::clear(){
    m_userData.clear();
//    m_outputFrame.clear();
}

SharedUserData IMessageProcessingUnit::user(){
    if(!m_userData)
        m_userData = SharedUserData(new UserData() );
    return m_userData;
}

void IMessageProcessingUnit::process(IClientRequest *req){
///FIXME
//    auto msg = m_outputFrame->add_response();
//    msg->CopyFrom( protobuf::ServerResponse::default_instance() );
//    msg->set_response_id( req.request_id() );
//    msg->set_code(protobuf::Error_MsgUnknown);
}

void IMessageProcessingUnit::process(DB &db, IClientRequest *req){
    process(req);
}

IServerResponse *IMessageProcessingUnit::response() {
    return m_response;
}

void IMessageProcessingUnit::prepareNewResponse()
{
    m_response->set_response_code( 0 );
    m_response->set_response_id( m_response_id++ );
    m_response->set_in_response_to(m_currentRequestId);
}

void IMessageProcessingUnit::sendServerError( IServerResponse::ResponseFlags e){
    response()->set_response_code( e );
}

