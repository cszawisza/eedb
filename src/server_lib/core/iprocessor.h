#pragma once
// interface allowing to create message parsers
#include <QObject>
#include <QSharedPointer>
#include <QDebug>
#include "message_conteiner.pb.h"
#include "clientcache.h"

using protbuf::MessageCapsule;
/**
 * @brief The IProcessor class
 */
class IProcessor
{

public:
    virtual ~IProcessor(){;}

    /**
     * @brief setWorkingCapsule
     * @param msg a capsule to process
     */
    void setWorkingCapsule( const MessageCapsule &msg ){
        m_inputMessage.Clear();
        m_inputMessage.CopyFrom(msg);
    }

    virtual bool checkUserState() {
        return cache()->userStatus().isLogged();
    }

    /**
     * @brief preProcess
     * @return true if everything is OK or
     * false if message is corrupted
     */
    virtual bool preProcess() = 0;

    /**
     * @brief process data given in setWorkingCapsule;
     */
    virtual void process() = 0;

    /**
     * @brief generateResponse
     * @return a ready to send capsule containing data
     */
    virtual QList<MessageCapsule> generateResponse() = 0;

    /**
     * @brief setClientCache
     * @param cache: sets a pointer to common cache (containing user status information and session stuf)
     */
    void setClientCache(QSharedPointer<ClientCache> cache){
        m_cache.swap(cache);
    }

protected:
    QSharedPointer<ClientCache> cache() {
        if( m_cache.isNull() )
            m_cache = QSharedPointer<ClientCache>( new ClientCache() );
        return m_cache;
    }

    MessageCapsule &inputMessage(){
        return m_inputMessage;
    }
    const MessageCapsule &inputMessage() const {
        return m_inputMessage;
    }

private:
    MessageCapsule m_inputMessage;
    QSharedPointer<ClientCache> m_cache;
};

/**
 * @brief The unknownMessage class returns a message
 * informing the client that this type of message is unsuported
 */
class UnknownMessageProcessor : public IProcessor
{
public:
    bool preProcess() Q_DECL_OVERRIDE
    {
        return true;
    }
    void process() Q_DECL_OVERRIDE
    {
        // unknown message handle
        // set proper output
    }

    QList<protbuf::MessageCapsule> generateResponse() Q_DECL_OVERRIDE
    {
        QList<protbuf::MessageCapsule> list;
        list << inputMessage();
        return list;
    }
};
