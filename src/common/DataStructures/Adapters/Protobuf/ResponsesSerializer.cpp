#include "ResponsesSerializer.hpp"

#include "ServerResponseAdapter.hpp"
#include "ClientRequestAdapter.hpp"

#include <message_conteiner.pb.h>

#include <QByteArray>

IClientRequest *ResponseSerializer::parseClientRequest(const QByteArray &a) const
{
    auto adp = new ClientRequest();
    parseClientRequest(a,adp);
    return adp;
}

void ResponseSerializer::parseClientRequest(const QByteArray &a, IClientRequest *req) const
{
    auto adp = dynamic_cast<ClientRequest*>(req);
    adp->rawPointer()->ParseFromArray(a.data(), a.size());
}

QByteArray ResponseSerializer::serializeServerResponse(IServerResponse *req) const
{
    auto adp = static_cast<ServerResponse*>(req);
    return {adp->rawPointer()->SerializeAsString().c_str(), adp->rawPointer()->ByteSize()};
}

void ResponseSerializer::serializeServerResponse(IServerResponse *req, QByteArray &) const
{

}
