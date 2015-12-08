#pragma once

#include <memory>

class QByteArray;

namespace data {

class IServerResponse;

class IResponsesDeserializer {
public:
    virtual ~IResponsesDeserializer() = default;

    virtual std::shared_ptr<IServerResponse> parseFromByteArray( const QByteArray& ) const = 0;
};
}
