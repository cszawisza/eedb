#pragma once

#include "../../IResponseDeserializer.hpp"

class ProtobufResponsesDesrializer : public data::IResponsesDeserializer {
public:
    std::shared_ptr<data::IServerResponse> parseFromByteArray(const QByteArray &) const;
};
