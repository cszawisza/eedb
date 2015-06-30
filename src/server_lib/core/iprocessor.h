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

using protbuf::ClientRequest;
using protbuf::ClientRequests;
/**
 * @brief The IProcessor class
 */

class MessageHandler
{
public:
    typedef QSharedPointer<protbuf::ClientRequests> SharedRequests;
    typedef QSharedPointer<protbuf::ServerResponses> SharedResponses;
    MessageHandler(){}
    virtual ~MessageHandler(){;}

    protbuf::ServerResponse getLastResponse(){
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
    virtual void process(protbuf::ClientRequest &req){
        auto msg = m_outputFrame->add_response();
        msg->CopyFrom( protbuf::ServerResponse::default_instance() );
        msg->set_responseid( req.requestid() );
        ResponseCode *codes = msg->mutable_msgserverresponse()->add_codes();
        codes->set_error(true);
        codes->set_code( protbuf::ServerErrorCodes::Error_MsgUnknown );
    }

protected:
    UserData *user(){
        if(!m_userData)
            m_userData = SharedUserData(new UserData() );
        return m_userData.data();
    }

    const bool addResponse( const protbuf::ServerResponse &resp ){
        if(!m_outputFrame)
            m_outputFrame = SharedResponses(new protbuf::ServerResponses);
        m_outputFrame->add_response()->MergeFrom(resp);
    }

private:
    SharedUserData m_userData;
    SharedResponses m_outputFrame;
};
