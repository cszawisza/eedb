#include "RequestSerializer.hpp"
#include "ServerResponse.hpp"

#include "ClientRequestAdapter.hpp"
#include "ServerResponseAdapter.hpp"

#include "message_conteiner.pb.h"
#include <QByteArray>

IServerResponse *RequestsSerializer::parseServerResponse(const QByteArray &a) const
{
        auto adp = new ServerResponse();
        parseServerResponse(a,adp);
        return adp;
}

void RequestsSerializer::parseServerResponse(const QByteArray &a, IServerResponse *res) const
{
    auto adp = dynamic_cast<ServerResponse*>(res);
    adp->rawPointer()->ParseFromArray(a.data(), a.size());
}

QByteArray RequestsSerializer::serializeClientRequest( IClientRequest* req) const
{
    auto adp = static_cast<ClientRequest*>(req);
    return {adp->rawPointer()->SerializeAsString().c_str(), adp->rawPointer()->ByteSize()};
}

void RequestsSerializer::serializeClientRequest(IClientRequest *req, QByteArray &ba) const
{
    auto adp = static_cast<ClientRequest*>(req);
    auto size = adp->rawPointer()->ByteSize();
    ba.clear();
    ba.reserve(size);
    ba.append(adp->rawPointer()->SerializeAsString().c_str(), size);
}
