#include <QByteArray>
#include <ProtobufConverters.hpp>

QByteArray convertProtobufClientRequestsToQByteArray(const pb::ClientRequests & p_clientRequests)
{
    return {p_clientRequests.SerializeAsString().c_str(),
            p_clientRequests.ByteSize()};
}

boost::optional<pb::ServerResponses> convertQByteArrayToProtobufServerResponse(const QByteArray & p_serverResponse)
{
    pb::ServerResponses l_serverResponse{};
    if(!l_serverResponse.ParseFromArray(p_serverResponse.data(), p_serverResponse.size()))
    {
        //qDebug() << "Could not parse server response";
        return boost::none;
    }
    return l_serverResponse;
}
