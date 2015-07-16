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
    virtual ~MessageHandler(){;}

    pb::ServerResponse getLastResponse(){
        if(m_outputFrame->response_size() == 0 )
            return pb::ServerResponse::default_instance();
        return m_outputFrame->response(m_outputFrame->response_size()-1);
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

    /**
     * @brief process data given in setWorkingCapsule;
     */
    virtual void process(pb::ClientRequest &req){
        auto msg = m_outputFrame->add_response();
        msg->CopyFrom( pb::ServerResponse::default_instance() );
        msg->set_responseid( req.requestid() );
        msg->set_code(pb::Error_MsgUnknown);
    }

    virtual void process(DB &db, pb::ClientRequest &req){
        process(req);
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

protected:
    bool addResponse( const pb::ServerResponse &resp ){
        if(!m_outputFrame)
            m_outputFrame = SharedResponses(new pb::ServerResponses);
        m_outputFrame->add_response()->CopyFrom(resp);
    }

    void sendAccesDeny(){
        pb::ServerResponse resp;
        resp.set_code( pb::Error_AccesDeny );
        addResponse( resp );
    }

//    void sendAccesDeny(const string &message){
//        pb::ServerResponse resp;
//        resp.set_code( pb::Error_AccesDeny );
//        addResponse( resp );
//    }

private:
    SharedUserData m_userData;
    SharedResponses m_outputFrame;
};
