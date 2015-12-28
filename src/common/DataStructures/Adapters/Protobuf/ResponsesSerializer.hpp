#pragma once

#include "../../IResponseSerializer.hpp"

class ResponseSerializer : public IResponseSerializer {
public:
    IClientRequest *parseClientRequest(const QByteArray &) const;
    void parseClientRequest(const QByteArray &a, IClientRequest*req) const;

    QByteArray serializeServerResponse(IServerResponse *req) const;
    void serializeServerResponse(IServerResponse *req, QByteArray&) const;
};
