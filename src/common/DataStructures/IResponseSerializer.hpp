#pragma once

class QByteArray;

class IClientRequest;
class IServerResponse;

class IResponseSerializer {
public:
    virtual ~IResponseSerializer() = default;

    virtual IClientRequest* parseClientRequest( const QByteArray& ) const = 0;
    virtual void parseClientRequest( const QByteArray &array, IClientRequest* ) const = 0;

    virtual QByteArray serializeServerResponse( IServerResponse *req ) const = 0;
    virtual void serializeServerResponse(IServerResponse *req, QByteArray& ) const = 0;
};
