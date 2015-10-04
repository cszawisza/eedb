#pragma once
// interface allowing to create message parsers
#include <QObject>
#include <QSharedPointer>
#include <QDebug>
#include <QSharedPointer>
#include "message_conteiner.pb.h"
#include "clientcache.h"
#include "database/idatabase.h"
#include "auth/acl.hpp"
#include <atomic>

using pb::ClientRequest;
using pb::ClientRequests;
/**
 * @brief The IProcessor class
 */

class MessageHandler
{
public:
    typedef QSharedPointer<pb::ClientRequests> SharedRequests;
    typedef QSharedPointer<pb::ServerResponses> SharedResponses;
    MessageHandler(){
        m_outputFrame = SharedResponses(new pb::ServerResponses );
    }
    virtual ~MessageHandler(){}

    pb::ServerResponse getLastResponse(){
        if(m_outputFrame->response_size() == 0 )
            return pb::ServerResponse::default_instance();
        return m_outputFrame->response(m_outputFrame->response_size()-1);
    }

    void setInputData( SharedRequests frame ){
        m_inputFrame.swap(frame);
    }

    void setOutputData( SharedResponses frame ){
        m_outputFrame.swap( frame );
    }

    /**
     * @brief setClientCache
     * @param cache: sets a pointer to common cache (containing user status information and session stuf)
     */
    void setUserData( SharedUserData userData){
        m_userData.swap(userData);
    }

    void process( int msgId ){
        auto req = m_inputFrame->mutable_request( msgId );
        m_currentRequestId = req->requestid();
        process(*req);
    }

    void clear(){
        m_userData.clear();
        m_outputFrame.clear();
    }

    SharedUserData user(){
        if(!m_userData)
            m_userData = SharedUserData(new UserData() );
        return m_userData;
    }

    size_t responseCount() const {
        return m_outputFrame ? m_outputFrame->response_size() :0;
    }
protected:
    /**
     * @brief process data given in setWorkingCapsule;
     */
    virtual void process(pb::ClientRequest &req);
    virtual void process(DB &db, pb::ClientRequest &req);
    pb::ServerResponse *add_response();
    void sendServerError(pb::ServerError e);

private:
    static std::atomic<quint64> m_response_id;
    quint64 m_currentRequestId = 0;
    SharedUserData m_userData;
    SharedResponses m_outputFrame;
    SharedRequests m_inputFrame;
};
