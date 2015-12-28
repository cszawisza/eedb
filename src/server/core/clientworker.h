#pragma once

#include <QObject>
#include <QThread>
#include <QSharedPointer>
#include <QHash>

#include "frameparser.h"
#include "iprocessor.h"
#include "clientcache.h"

/**
 * @brief The ClientWorker class
 * Class hes responsibility to process recieved binary messages
 */
class ClientWorker : public QObject
{
    Q_OBJECT
public:
    typedef QSharedPointer<protobuf::ClientRequest> SharedRequests;
    typedef QSharedPointer<protobuf::ServerResponse> SharedResponses;
    explicit ClientWorker(QObject *parent = 0);

    void printMessageInfo(const protobuf::ClientRequest &request);
    void processMessages();
signals:
    /**
     * @brief jobFinished signal emmited when worker ends processing data
     */
    void jobFinished();

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
    SharedUserData m_cache;
    SharedResponses m_responseFrame;
    SharedRequests m_inputFrame;
    QHash<protobuf::ClientRequest::DataCase, QSharedPointer<IMessageProcessingUnit>> m_msgHandlers;
    QSharedPointer<IMessageProcessingUnit> m_defaultProcessor;
};
