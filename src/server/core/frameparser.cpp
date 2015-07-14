#include "frameparser.h"
RequestsDecoder::RequestsDecoder(QByteArray ba):
    m_rawMessage(ba)
{
}

bool RequestsDecoder::decodeTo(SharedRequests &frame){
    if(!frame)
        frame = SharedRequests(new pb::ClientRequests );
    return frame->ParseFromArray(m_rawMessage.data(), m_rawMessage.size() );
}

void RequestsDecoder::setData(QByteArray ba){
    m_rawMessage = ba;
}
