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
/**
 * @brief The IProcessor class
 */

class IMessageProcessingUint
{
public:
    typedef QSharedPointer<pb::ClientRequest> SharedRequest;
//    typedef QSharedPointer<pb::ClientRequest> SharedRequest;


    IMessageProcessingUint();
    virtual ~IMessageProcessingUint(){}
    pb::ServerResponse getLastResponse();
//    void setInputData( SharedRequest frame );
//    void setOutputData( SharedResponses frame );

    /**
     * @brief setClientCache
     * @param cache: sets a pointer to common cache (containing user status information and session stuf)
     */
    void setUserData( SharedUserData userData);
    void process( int msgId );
    void clear();
    SharedUserData user();
    size_t responseCount() const;
protected:
    virtual void process(pb::ClientRequest &req);
    virtual void process(DB &db, pb::ClientRequest &req);

    pb::ServerResponse *add_response();
    void sendServerError(pb::ServerError e);

private:
    static std::atomic<quint64> m_response_id;
    quint64 m_currentRequestId = 0;
    SharedUserData m_userData;
};
