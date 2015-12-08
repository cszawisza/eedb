#include <QByteArray>
#include <ProtobufConverters.hpp>
#include <QDebug>

QByteArray convertProtobufClientRequestsToQByteArray(const pb::ClientRequest & p_clientRequest)
{
    return {p_clientRequest.SerializeAsString().c_str(),
            p_clientRequest.ByteSize()};
}

boost::optional<pb::ServerResponse> convertQByteArrayToProtobufServerResponse(const QByteArray & p_serverResponse)
{
    pb::ServerResponse l_serverResponse{};
    if(!l_serverResponse.ParseFromArray(p_serverResponse.data(), p_serverResponse.size()))
    {
        qDebug() << "Could not parse server response";
        return boost::none;
    }
    return l_serverResponse;
}
