#pragma once

class QByteArray;

class IClientRequest;
class IServerResponse;

class IResponseSerializer {
public:
    virtual ~IResponseSerializer() = default;

    virtual IClientRequest* parseFromByteArray( const QByteArray& ) const = 0;
    virtual void parseFromByteArray( const QByteArray &array, IClientRequest* ) const = 0;

    virtual QByteArray serializeToByteArray( IServerResponse *req ) const = 0;
    virtual void serializeToByteArray(IServerResponse *req, QByteArray& ) const = 0;
};
