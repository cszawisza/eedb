#pragma once

#include <functional>
#include <boost/optional.hpp>
#include "message_conteiner.pb.h"

class QByteArray;

using ProtobufToQByteArrayConverter = std::function<QByteArray(const pb::ClientRequest &)>;
using QByteArrayToProtobufConverter = std::function<boost::optional<pb::ServerResponse>(const QByteArray &)>;

QByteArray convertProtobufClientRequestsToQByteArray(const pb::ClientRequest &p_clientRequest);
boost::optional<pb::ServerResponse> convertQByteArrayToProtobufServerResponse(const QByteArray & p_serverResponse);
