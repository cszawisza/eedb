#pragma once

#include <functional>
#include <boost/optional.hpp>
#include "message_conteiner.pb.h"

class QByteArray;

using ProtobufToQByteArrayConverter = std::function<QByteArray(const pb::ClientRequests &)>;
using QByteArrayToProtobufConverter = std::function<boost::optional<pb::ServerResponses>(const QByteArray &)>;

QByteArray convertProtobufClientRequestsToQByteArray(const pb::ClientRequests & p_clientRequests);
boost::optional<pb::ServerResponses> convertQByteArrayToProtobufServerResponse(const QByteArray & p_serverResponse);
