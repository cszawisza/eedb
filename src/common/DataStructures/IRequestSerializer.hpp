#pragma once

class QByteArray;

class IClientRequest;
class IServerResponse;

class IRequestsSerializer {
public:
    virtual ~IRequestsSerializer() = default;

    virtual IServerResponse* parseServerResponse( const QByteArray& ) const = 0;
    virtual void parseServerResponse( const QByteArray&, IServerResponse* ) const = 0;

    virtual QByteArray serializeClientRequest( IClientRequest *req ) const = 0;
    virtual void serializeClientRequest( IClientRequest *req, QByteArray&ba ) const = 0;
};
