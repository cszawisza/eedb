#pragma once

class QByteArray;

namespace data {

class IClientRequests;

class IRequestsSerializer {
public:
    virtual ~IRequestsSerializer() = default;

    virtual QByteArray serializeToByteArray( IClientRequests *req ) const = 0;
};

}
