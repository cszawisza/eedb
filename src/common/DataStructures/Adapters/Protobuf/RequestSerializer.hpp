#pragma once

#include "../../IRequestSerializer.hpp"

class ProtobufRequestsSerializer : public IRequestsSerializer {
public:
    QByteArray serializeToByteArray(IClientRequest *req) const override;
    void serializeToByteArray(IClientRequest *req, QByteArray &ba ) const override;

    IServerResponse *parseFromByteArray(const QByteArray &a) const override;
    void parseFromByteArray(const QByteArray &a, IServerResponse *) const override;
};
