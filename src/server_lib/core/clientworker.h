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
    explicit ClientWorker(QObject *parent = 0);

    void printMessageInfo(const protbuf::MessageCapsule &message);
    void processData();
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
     * @param frame a protbuf message (MessageFrame) containing MessageCapsules with encapsuled information
     */
    void processBinnaryMessage(const QByteArray frame);
private:
    protbuf::MessageFrame m_responseFrame;
    QHash<MsgType, QSharedPointer<IProcessor>> m_messageProcessors;
    FrameParser m_frameParser;
    QSharedPointer<ClientCache> m_cache;
    QSharedPointer<IProcessor> m_defaultProcessor;
};
