#include "RequestSerializer.hpp"
#include "ServerResponse.hpp"

#include "ClientRequestAdapter.hpp"
#include "ServerResponseAdapter.hpp"

#include "message_conteiner.pb.h"
#include <QByteArray>

IServerResponse *ProtobufRequestsSerializer::parseFromByteArray(const QByteArray &a) const
{
        auto adp = new ProtobufServerResponseAdapter();
        parseFromByteArray(a,adp);
        return adp;
}

void ProtobufRequestsSerializer::parseFromByteArray(const QByteArray &a, IServerResponse *res) const
{
    auto adp = dynamic_cast<ProtobufServerResponseAdapter*>(res);
    adp->rawPointer()->ParseFromArray(a.data(), a.size());
}

QByteArray ProtobufRequestsSerializer::serializeToByteArray( IClientRequest* req) const
{
    auto adp = static_cast<ProtobufClientRequestAdapter*>(req);
    return {adp->rawPointer()->SerializeAsString().c_str(), adp->rawPointer()->ByteSize()};
}

void ProtobufRequestsSerializer::serializeToByteArray(IClientRequest *req, QByteArray &ba) const
{
    auto adp = static_cast<ProtobufClientRequestAdapter*>(req);
    auto size = adp->rawPointer()->ByteSize();
    ba.clear();
    ba.reserve(size);
    ba.append(adp->rawPointer()->SerializeAsString().c_str(), size);
}
