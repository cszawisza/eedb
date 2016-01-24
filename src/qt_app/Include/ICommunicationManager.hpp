#pragma once
#include <QObject>
#include <QSharedPointer>
#include <QUrl>


#include <Interfaces/CategoryResponses.hpp>
#include <Interfaces/UserResponses.hpp>

class ISerializableData;
class ISocket;
class Url;

namespace responses{
class IUser;
class ICategory;
}

//struct ResponseMetadata{
////    ResponseMetadata():
////        ResponseMetadata( protobuf::ServerResponse::default_instance() ){}
////    ResponseMetadata(const protobuf::ServerResponse &res){
////        response_id = res.response_id();
////        in_response_to = res.in_response_to();
////        is_last_response = res.is_last_response();
////    }

//    quint64 response_id;
//    quint64 in_response_to;
//    bool is_last_response;
//};

//struct RequestMetadata{
////    RequestMetadata():
////        RequestMetadata( IClientRequest &req){}
////    RequestMetadata( const IClientRequest &req ){
////        request_id = req.get_requestId();
////    }

//    uint64_t request_id;
//};

//Q_DECLARE_METATYPE(ResponseMetadata)
//Q_DECLARE_METATYPE(RequestMetadata)

class IClientRequest;

class IUserCommunicationManager : public QObject{
    Q_OBJECT
public:
    virtual ~IUserCommunicationManager(){}

    virtual IClientRequest *newRequest() = 0;
    virtual void sendRequest( ) = 0;
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

signals:
    void receivedMessage( const responses::IUser &) const;
    void receivedMessage( const responses::ICategory &) const;

    void socketConnected() const;
    void socketDisconnected() const;
    void loggedin() const;
    void logout() const;
};
