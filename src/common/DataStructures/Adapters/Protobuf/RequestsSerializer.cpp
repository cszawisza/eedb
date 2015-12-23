#include "RequestsSerializer.hpp"
#include "ClientRequestAdapter.hpp"
#include "message_conteiner.pb.h"
#include <QByteArray>

QByteArray ProtobufRequestsSerializer::serializeToByteArray( IClientRequest* req) const
{
    auto adp = static_cast<ProtobufClientRequestAdapter*>(req);
//    auto adp = std::dynamic_pointer_cast<ClientRequestAdapter>(req);
    return {adp->rawPointer()->SerializeAsString().c_str(), adp->rawPointer()->ByteSize()};
}

