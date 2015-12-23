#pragma once

#include <memory>

class QByteArray;

class IClientRequest;

class IRequestsDeserializer {
public:
    virtual ~IRequestsDeserializer() = default;

    virtual std::shared_ptr<IClientRequest> parseFromByteArray( const QByteArray& ) const = 0;
};

