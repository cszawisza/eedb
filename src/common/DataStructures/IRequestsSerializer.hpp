#pragma once

#include <memory>

class QByteArray;

class IClientRequest;

class IRequestsSerializer {
public:
    virtual ~IRequestsSerializer() = default;

    virtual QByteArray serializeToByteArray( IClientRequest *req ) const = 0;
};
