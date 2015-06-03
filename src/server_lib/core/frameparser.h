#pragma once

#include <QByteArray>
#include "message_conteiner.pb.h"

/**
 * @brief The FrameParser class
 * class parses 'main' protbuf message whih is then
 * divided into individual protbuf messages
 */
class FrameParser
{
public:
    explicit FrameParser();

    /**
     * @brief prepareMessages set the data reference into parser
     * @param ba a whole binarry message (frame containing messages)
     * @throws std::exception
     */
    void prepareMessages(const QByteArray &ba);

    int messagesCount() const Q_DECL_NOEXCEPT;
    bool hasPandingMessags() const Q_DECL_NOEXCEPT;
    const protbuf::MessageCapsule &nextPandingMessage() Q_DECL_NOEXCEPT;

private:
    int m_currentMsg;
    protbuf::MessageFrame m_frame;
};
