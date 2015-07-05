#pragma once
// interface allowing to create message parsers
#include <QObject>
#include <QSharedPointer>
#include <QDebug>
#include <QSharedPointer>
#include "message_conteiner.pb.h"
#include "clientcache.h"
#include "idatabase.h"
#include "acl.h"

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
    MessageHandler(){}
    virtual ~MessageHandler(){;}

    pb::ServerResponse getLastResponse(){
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
        ResponseCode *codes = msg->mutable_msgserverresponse()->add_codes();
        codes->set_error(true);
        codes->set_code( pb::ServerErrorCodes::Error_MsgUnknown );
    }

    void clear(){
        m_userData.clear();
        m_outputFrame.clear();
    }

protected:
    UserData *user(){
        if(!m_userData)
            m_userData = SharedUserData(new UserData() );
        return m_userData.data();
    }

    const bool addResponse( const pb::ServerResponse &resp ){
        if(!m_outputFrame)
            m_outputFrame = SharedResponses(new pb::ServerResponses);
        m_outputFrame->add_response()->MergeFrom(resp);
    }

private:
    SharedUserData m_userData;
    SharedResponses m_outputFrame;
};
