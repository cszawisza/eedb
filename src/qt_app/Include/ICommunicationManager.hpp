#pragma once
#include <QObject>
#include <QSharedPointer>
#include <QUrl>

#include "Interfaces/ClientRequest.hpp"
#include "Interfaces/ServerResponse.hpp"

class ISocket;
class Url;

/**
 * @brief The ICommunicationManager class handles the communication between client and serwer
 * also holds a container of
 */

struct ResponseMetadata{
//    ResponseMetadata():
//        ResponseMetadata( protobuf::ServerResponse::default_instance() ){}
//    ResponseMetadata(const protobuf::ServerResponse &res){
//        response_id = res.response_id();
//        in_response_to = res.in_response_to();
//        is_last_response = res.is_last_response();
//    }

    quint64 response_id;
    quint64 in_response_to;
    bool is_last_response;
};

struct RequestMetadata{
//    RequestMetadata():
//        RequestMetadata( IClientRequest &req){}
//    RequestMetadata( const IClientRequest &req ){
//        request_id = req.get_requestId();
//    }

    uint64_t request_id;
};

Q_DECLARE_METATYPE(ResponseMetadata)
Q_DECLARE_METATYPE(RequestMetadata)


class ICommunicationManager : public QObject{
    Q_OBJECT
public:
    virtual ~ICommunicationManager(){}

    /**
     * @brief newRequest
     * @return new a pointer to ClientRequests structure held in Communication Manager body
     */
//    virtual protobuf::ClientRequest *newRequest( uint64_t &request_id ) = 0;

public slots:
    /**
     * @brief openConnection, try to open a socket
     * @param url to open
     */
    virtual void openConnection( const Url &url ) const = 0;

    /**
     * @brief closeConnection logout and close connection to server
     */
    virtual void closeConnection( ) const = 0;
//    virtual void loginToServerAs( const QString &name, const QString &password) const =0;

    /**
     * @brief sendUserRequest
     * @param data
     */
    virtual void sendUserRequest( IClientRequest* data) = 0;

signals:
    void socketConnected() const;
    void socketDisconnected() const;
    void loggedin() const;
    void logout() const;

//    void userRequestSent( RequestMetadata meta );
//    void userResponse( ResponseMetadata meta, std::shared_ptr<protobuf::UserRes> data);
};
