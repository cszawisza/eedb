#include "iprocessor.h"

std::atomic<quint64> MessageHandler::m_response_id;

void MessageHandler::process(pb::ClientRequest &req){
    auto msg = m_outputFrame->add_response();
    msg->CopyFrom( pb::ServerResponse::default_instance() );
    msg->set_responseid( req.requestid() );
    msg->set_code(pb::Error_MsgUnknown);
}

void MessageHandler::process(DB &db, pb::ClientRequest &req){
    process(req);
}

pb::ServerResponse *MessageHandler::add_response() {
    if(!m_outputFrame)
        m_outputFrame = SharedResponses(new pb::ServerResponses);
    auto res = m_outputFrame->add_response();
    res->CopyFrom(pb::ServerResponse::default_instance());
    res->set_responseid( m_response_id++ );
    res->set_in_response_to(m_currentRequestId);
    return res;
}

void MessageHandler::sendServerError( pb::ServerError e){
    auto res = add_response();
    res->set_code( e );
}

