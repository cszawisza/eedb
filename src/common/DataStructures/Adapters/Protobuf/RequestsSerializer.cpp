#include "RequestsSerializer.hpp"
#include "ClientRequestAdapter.hpp"

#include <QByteArray>

QByteArray ProtobufRequestsSerializer::serializeToByteArray(data::IClientRequests *req) const
{
    ProtobufClientRequestsAdapter *adp = dynamic_cast<ProtobufClientRequestsAdapter*>(req);

    adp->form();

    return {adp->SerializeAsString().c_str(), adp->ByteSize()};
}

