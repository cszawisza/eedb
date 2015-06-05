#pragma once
// interface allowing to create message parsers
#include <QObject>
#include <QSharedPointer>
#include <QDebug>
#include <QSharedPointer>
#include "message_conteiner.pb.h"
#include "clientcache.h"

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
    virtual ~MessageHandler(){;}

    /// working input frame
    void setInputData( SharedRequests frame ){
        m_inputFrame.swap(frame);
    }

    /// set the index of message that we work on
    /// returns false when type of message not fits or when index exceds message number
    bool setWorkingMessage( int index ){
        m_messageIndex = index;
        return true;
    }

    void setOutputData( SharedResponses frame ){
        m_outputFrame.swap( frame );
    }

    /**
     * @brief setClientCache
     * @param cache: sets a pointer to common cache (containing user status information and session stuf)
     */
    void setClientCache( SharedClientCache cache){
        m_cache.swap(cache);
    }


    /**
     * @brief process data given in setWorkingCapsule;
     */
    virtual void process(){
        auto msg = m_outputFrame->add_response();
        msg->CopyFrom( protbuf::ServerResponse::default_instance() );
        msg->set_responseid( m_inputFrame->request(m_messageIndex).requestid() );
        ResponseCode *codes = msg->mutable_msgserverresponse()->add_codes();
        codes->set_error(true);
        codes->set_code( protbuf::ServerErrorCodes::Error_MsgUnknown );
    }

protected:
    SharedClientCache cache(){
        return m_cache;
    }

private:
    SharedClientCache m_cache;
    SharedRequests m_inputFrame;
    SharedResponses m_outputFrame;
    int m_messageIndex;
};
