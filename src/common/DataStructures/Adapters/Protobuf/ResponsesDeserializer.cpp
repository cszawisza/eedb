#include "ResponsesDeserializer.hpp"
#include "message_conteiner.pb.h"
#include <QByteArray>

std::shared_ptr<data::IServerResponse> ProtobufResponsesDesrializer::parseFromByteArray(const QByteArray &) const
{
//    auto adp = std::make_shared<ProtobufClientRequestAdapter>();
//    adp->rawPointer()->ParseFromArray(a.data(), a.size());
//    return adp;
    return std::shared_ptr<data::IServerResponse>();
}
