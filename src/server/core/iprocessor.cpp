#include "iprocessor.h"

std::atomic<quint64> IMessageProcessingUint::m_response_id;

IMessageProcessingUint::IMessageProcessingUint(){
    m_outputFrame = SharedResponses(new pb::ServerResponses );
}

pb::ServerResponse IMessageProcessingUint::getLastResponse(){
    if(m_outputFrame->response_size() == 0 )
        return pb::ServerResponse::default_instance();
    return m_outputFrame->response(m_outputFrame->response_size()-1);
}

void IMessageProcessingUint::setInputData(IMessageProcessingUint::SharedRequest frame){
    m_inputFrame.swap(frame);
}

void IMessageProcessingUint::setOutputData(IMessageProcessingUint::SharedResponses frame){
    m_outputFrame.swap( frame );
}

void IMessageProcessingUint::setUserData(SharedUserData userData){
    m_userData.swap(userData);
}

void IMessageProcessingUint::process(int msgId){
    auto req = m_inputFrame->mutable_request( msgId );
    m_currentRequestId = req->request_id();
    process(*req);
}

void IMessageProcessingUint::clear(){
    m_userData.clear();
    m_outputFrame.clear();
}

SharedUserData IMessageProcessingUint::user(){
    if(!m_userData)
        m_userData = SharedUserData(new UserData() );
    return m_userData;
}

size_t IMessageProcessingUint::responseCount() const {
    return m_outputFrame ? m_outputFrame->response_size() :0;
}

void IMessageProcessingUint::process(pb::ClientRequest &req){
    auto msg = m_outputFrame->add_response();
    msg->CopyFrom( pb::ServerResponse::default_instance() );
    msg->set_response_id( req.request_id() );
    msg->set_code(pb::Error_MsgUnknown);
}

void IMessageProcessingUint::process(DB &db, pb::ClientRequest &req){
    process(req);
}

pb::ServerResponse *IMessageProcessingUint::add_response() {
    if(!m_outputFrame)
        m_outputFrame = SharedResponses(new pb::ServerResponses);
    auto res = m_outputFrame->add_response();
    res->CopyFrom(pb::ServerResponse::default_instance());
    res->set_response_id( m_response_id++ );
    res->set_in_response_to(m_currentRequestId);
    return res;
}

void IMessageProcessingUint::sendServerError( pb::ServerError e){
    auto res = add_response();
    res->set_code( e );
}

