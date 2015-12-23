#include "ResponsesSerializer.hpp"

#include "ServerResponseAdapter.hpp"
#include "ClientRequestAdapter.hpp"

#include <message_conteiner.pb.h>

#include <QByteArray>

IClientRequest *ProtobufResponseSerializer::parseFromByteArray(const QByteArray &a) const
{
    auto adp = new ProtobufClientRequestAdapter();
    parseFromByteArray(a,adp);
    return adp;
}

void ProtobufResponseSerializer::parseFromByteArray(const QByteArray &a, IClientRequest *req) const
{
    auto adp = dynamic_cast<ProtobufClientRequestAdapter*>(req);
    adp->rawPointer()->ParseFromArray(a.data(), a.size());
}

QByteArray ProtobufResponseSerializer::serializeToByteArray(IServerResponse *req) const
{
    auto adp = static_cast<ProtobufServerResponseAdapter*>(req);
    return {adp->rawPointer()->SerializeAsString().c_str(), adp->rawPointer()->ByteSize()};
}

void ProtobufResponseSerializer::serializeToByteArray(IServerResponse *req, QByteArray &) const
{

}
