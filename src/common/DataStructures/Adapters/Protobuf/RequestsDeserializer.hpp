#pragma once

#include "../../IRequestsDeserializer.hpp"

class ProtobufRequestsDeserializer : public IRequestsDeserializer {
    // IRequestsDeserializer interface
public:
    std::shared_ptr<IClientRequest> parseFromByteArray(const QByteArray &) const;
};
