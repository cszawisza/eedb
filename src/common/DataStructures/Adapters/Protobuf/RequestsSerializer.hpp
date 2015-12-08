#pragma once

#include "../../IRequestsSerializer.hpp"

class ProtobufRequestsSerializer : public data::IRequestsSerializer {
    // IRequestsSerializer interface
public:
    QByteArray serializeToByteArray(data::IClientRequest *req) const;
};
