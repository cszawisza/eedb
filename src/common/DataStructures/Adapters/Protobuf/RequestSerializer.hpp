#pragma once

#include "../../IRequestSerializer.hpp"

class RequestsSerializer : public IRequestsSerializer {
public:
    QByteArray serializeClientRequest(IClientRequest *req) const override;
    void serializeClientRequest(IClientRequest *req, QByteArray &ba ) const override;

    IServerResponse *parseServerResponse(const QByteArray &a) const override;
    void parseServerResponse(const QByteArray &a, IServerResponse *) const override;
};
