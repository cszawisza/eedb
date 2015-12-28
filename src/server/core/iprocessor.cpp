#include "iprocessor.h"

#include <DataStructures/Adapters/Protobuf/ClientRequestAdapter.hpp>
#include <DataStructures/Adapters/Protobuf/ServerResponseAdapter.hpp>

std::atomic<quint64> IMessageProcessingUnit::m_response_id;


IMessageProcessingUnit::IMessageProcessingUnit(){
    ///FIXME
//    m_outputFrame = SharedResponses(new protobuf::ServerResponses );
}

///FIXME
//IServerResponse IMessageProcessingUint::getLastResponse(){
//    if(m_outputFrame->response_size() == 0 )
//        return protobuf::ServerResponse::default_instance();
//    return m_outputFrame->response(m_outputFrame->response_size()-1);
//}

///FIXME
//void IMessageProcessingUnit::setInputData(IMessageProcessingUnit::SharedRequest frame){
//    m_inputFrame.swap(frame);
//}

///FIXME
//void IMessageProcessingUnit::setOutputData(IMessageProcessingUnit::SharedResponses frame){
//    m_outputFrame.swap( frame );
//}

void IMessageProcessingUnit::setUserData(SharedUserData userData){
    m_userData.swap(userData);
}

void IMessageProcessingUnit::process(int msgId){
//    auto req = m_inputFrame->mutable_request( msgId );
//    m_currentRequestId = req->request_id();
//    process(*req);
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

size_t IMessageProcessingUnit::responseCount() const {
    ///FIXME
    return 1;
//    return m_outputFrame ? m_outputFrame->response_size() :0;
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

IServerResponse *IMessageProcessingUnit::add_response() {
//    if(!m_outputFrame)
//        m_outputFrame = SharedResponses(new protobuf::ServerResponses);
    auto res = new ServerResponse();//m_outputFrame->add_response();
    res->set_response_id( m_response_id++ );
    res->set_in_response_to(m_currentRequestId);
    return res;
}

void IMessageProcessingUnit::sendServerError(int e){
//    auto res = add_response();
    auto res = new ServerResponse();
    res->set_response_code( e );
}

