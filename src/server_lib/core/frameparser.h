#pragma once

#include <QByteArray>
#include <QSharedPointer>

#include "message_conteiner.pb.h"

///TODO remove if not needed

/**
 * @brief The FrameParser class
 * class parses 'main' protbuf message whih is then
 * divided into individual protbuf messages
 */
class RequestsDecoder
{
public:
    typedef QSharedPointer<pb::ClientRequests> SharedRequests;

    explicit RequestsDecoder(QByteArray ba);
    bool decodeTo( SharedRequests &frame );
    void setData(QByteArray ba);
private:
    QByteArray m_rawMessage;
 };
