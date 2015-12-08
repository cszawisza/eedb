#pragma once

#include <QByteArray>
#include <QSharedPointer>

#include "message_conteiner.pb.h"

/**
 * @brief The FrameParser class
 * class parses 'main' protbuf message whih is then
 * divided into individual protbuf messages
 */
class RequestsDecoder
{
public:
    explicit RequestsDecoder(QByteArray ba);
    bool decodeTo(pb::ClientRequest &frame );
    void setData(QByteArray ba);
private:
    QByteArray m_rawMessage;
 };
