#pragma once

#include "../../IRequestsSerializer.hpp"

class ProtobufRequestsSerializer : public IRequestsSerializer {
    // IRequestsSerializer interface
public:
    QByteArray serializeToByteArray(IClientRequest *req) const;
};
