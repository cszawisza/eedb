#pragma once

#include <QObject>
#include <QThread>
#include <QSharedPointer>
#include <QHash>

#include "iprocessor.h"
#include "clientcache.h"
#include "Interfaces/DefinedActions.hpp"

/**
 * @brief The ClientWorker class
 * Class hes responsibility to process recieved binary messages
 */
class ClientWorker : public QObject
{
    Q_OBJECT
public:
    explicit ClientWorker(QObject *parent = 0);

    void processMessage();
signals:
    /**
     * @brief beforeProcessing signal emited before worker atempts to parse message
     */
    void beforeProcessing();

    /**
     * @brief afterProcessing signal emmited when worker ends processing data
     */
    void afterProcessing();

    /**
     * @brief binnaryMessageReadyToSend: Signal emmited every time a package can be send
     * @param data: encapsulated protbuf message
     */
    void binnaryMessageReadyToSend(const QByteArray &data);

    /**
     * @brief messageCorrupted signal emmited whed a frame is corrupted
     */
    void messageCorrupted( quint32 msgid );
public slots:

    /**
     * @brief processBinnaryMessage: is responsible for handling message
     * @param frame a protbuf message (MessageFrame) containing Messages with encapsuled information
     */
    void processBinnaryMessage(QByteArray frame);
private:
    void printMessageInfo(const IMessageContainer *request);

    std::shared_ptr<UserData> m_cache;
    std::shared_ptr<IServerResponse> m_response;
    std::shared_ptr<IClientRequest> m_request;

    QHash<ActionTypeId, QSharedPointer<IMessageProcessingUnit>> m_msgHandlers;
    QSharedPointer<IMessageProcessingUnit> m_defaultProcessor;
};
