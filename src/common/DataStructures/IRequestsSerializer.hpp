#pragma once

#include <memory>

class QByteArray;

namespace data {

class IClientRequest;

class IRequestsSerializer {
public:
    virtual ~IRequestsSerializer() = default;

    virtual QByteArray serializeToByteArray( data::IClientRequest *req ) const = 0;
};

}
