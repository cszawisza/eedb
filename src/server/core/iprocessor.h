#pragma once
// interface allowing to create message parsers
#include <atomic>

#include <QObject>
#include <QSharedPointer>
#include <QDebug>

#include "clientcache.h"
#include "database/idatabase.h"
#include "auth/acl.hpp"

#include <Interfaces/ClientRequest.hpp>
#include <Interfaces/ServerResponse.hpp>

/**
 * @brief The IProcessor class
 */

class IMessageProcessingUnit
{
public:
    IMessageProcessingUnit();
    virtual ~IMessageProcessingUnit(){}
    /**
     * @brief setClientCache
     * @param cache: sets a pointer to common cache (containing user status information and session stuf)
     */
    void setUserData( SharedUserData userData);

    void setOutputData( IServerResponse *frame );

    void clear();
    SharedUserData user();

    virtual void process(IClientRequest *req);
    virtual void process(DB &db, IClientRequest *req);

    IServerResponse *response();
    void prepareNewResponse();
    void sendServerError(IServerResponse::ResponseFlags e );

private:
    static std::atomic<quint64> m_response_id;
    quint64 m_currentRequestId = 0;
    SharedUserData m_userData;
    IServerResponse *m_response;
};
