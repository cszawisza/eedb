#pragma once

#include "../../IResponseSerializer.hpp"

class ProtobufResponseSerializer : public IResponseSerializer {
public:
    IClientRequest *parseFromByteArray(const QByteArray &) const;
    void parseFromByteArray(const QByteArray &a, IClientRequest*req) const;

    QByteArray serializeToByteArray(IServerResponse *req) const;
    void serializeToByteArray(IServerResponse *req, QByteArray&) const;
};
