#include "RequestsDeserializer.hpp"
#include "ClientRequestAdapter.hpp"
#include "message_conteiner.pb.h"
#include <QByteArray>

std::shared_ptr<data::IClientRequest> ProtobufRequestsDeserializer::parseFromByteArray(const QByteArray &a) const
{
    auto adp = std::make_shared<ProtobufClientRequestAdapter>();
    adp->rawPointer()->ParseFromArray(a.data(), a.size());
    return adp;
}
