#pragma once

class QByteArray;

class IClientRequest;
class IServerResponse;

class IRequestsSerializer {
public:
    virtual ~IRequestsSerializer() = default;

    virtual IServerResponse* parseFromByteArray( const QByteArray& ) const = 0;
    virtual void parseFromByteArray( const QByteArray&, IServerResponse* ) const = 0;

    virtual QByteArray serializeToByteArray( IClientRequest *req ) const = 0;
    virtual void serializeToByteArray( IClientRequest *req, QByteArray&ba ) const = 0;
};
