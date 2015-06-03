#include "frameparser.h"
FrameParser::FrameParser()
{
}

void FrameParser::prepareMessages(const QByteArray &ba) {
    ///TODO posible race odition
    m_currentMsg = 0;
    m_frame.ParseFromArray(ba.data(), ba.size() );
}

int FrameParser::messagesCount() const Q_DECL_NOEXCEPT
{
    return m_frame.capsules_size();
}

bool FrameParser::hasPandingMessags() const Q_DECL_NOEXCEPT
{
    return messagesCount() > m_currentMsg;
}

const protbuf::MessageCapsule &FrameParser::nextPandingMessage() Q_DECL_NOEXCEPT
{
    return m_frame.capsules(m_currentMsg++);
}
