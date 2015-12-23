#pragma once

#include "../../IResponseDeserializer.hpp"

class ProtobufResponsesDesrializer : public IResponsesDeserializer {
public:
    std::shared_ptr<IServerResponse> parseFromByteArray(const QByteArray &) const;
};
