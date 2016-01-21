#pragma once
// interface allowing to create message parsers
#include <atomic>

#include "clientcache.h"

#include <Interfaces/ClientRequest.hpp>
#include <Interfaces/ServerResponse.hpp>

/**
 * @brief The IProcessor class
 */
class DB;

class IMessageProcessingUnit
{
public:
    IMessageProcessingUnit();
    virtual ~IMessageProcessingUnit(){}
    /**
     * @brief setClientCache
     * @param cache: sets a pointer to common cache (containing user status information and session stuf)
     */
    void setUserData( std::shared_ptr<UserData> userData);

    void setOutputData(std::shared_ptr<IServerResponse> frame );

    void clear();
    std::shared_ptr<UserData> user();

    virtual void process(IClientRequest *req);
    virtual void process(DB &db, IClientRequest *req);

    IServerResponse *response();
    void prepareNewResponse();
    void sendServerError(IServerResponse::ResponseFlags e );

private:
    static std::atomic<quint64> m_response_id;
    std::shared_ptr<UserData> m_userData;
    std::shared_ptr<IServerResponse> m_response;
};
