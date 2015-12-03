#pragma once

class QByteArray;

namespace data {

class IClientRequests;

class IRequestsDeserializer {
    virtual ~IRequestsDeserializer() = default;

    virtual IClientRequests *parseFromByteArray( const QByteArray& ) const = 0;
};

}
