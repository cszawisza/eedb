#pragma once

#include "../../IRequestsDeserializer.hpp"

class ProtobufRequestsDeserializer : public data::IRequestsDeserializer {
    // IRequestsDeserializer interface
public:
    std::shared_ptr<data::IClientRequest> parseFromByteArray(const QByteArray &) const;
};
