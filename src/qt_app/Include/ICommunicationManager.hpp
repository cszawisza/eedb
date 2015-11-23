#pragma once
#include <QObject>
#include <memory>
#include <QSharedPointer>
#include "message_conteiner.pb.h"

class ISocket;

/**
 * @brief The ICommunicationManager class handles the communication between client and serwer
 * also holds a container of
 */

struct ResponseMetadata{
    ResponseMetadata():
        ResponseMetadata( pb::ServerResponse::default_instance() ){}
    ResponseMetadata(const pb::ServerResponse &res){
        response_id = res.response_id();
        in_response_to = res.in_response_to();
        is_last_response = res.is_last_response();
    }

    quint64 response_id;
    quint64 in_response_to;
    bool is_last_response;
};

struct RequestMetadata{
    RequestMetadata():
        RequestMetadata( pb::ClientRequest::default_instance() ){}
    RequestMetadata( const pb::ClientRequest &req ){
        request_id = req.request_id();
    }

    uint64_t request_id;
};

Q_DECLARE_METATYPE(ResponseMetadata)
Q_DECLARE_METATYPE(RequestMetadata)

Q_DECLARE_METATYPE( std::shared_ptr<pb::UserRes> )
Q_DECLARE_METATYPE( std::shared_ptr<pb::CategoryRes> )

class ICommunicationManager : public QObject{
    Q_OBJECT
public:
    enum CommunicationError {
        CommunicationErrorNone,
        CommunicationErrorSocketNotConnected
    };

    enum ConnectionState {
        UnconnectedState,
        ConnectingState,
        ConnectedNotLoggedState,
        ConnectedAndLoggedState, // when connected via socket to host, ald loged in to server
        ClosingState
    };

    ICommunicationManager():
    QObject(){}
    virtual ~ICommunicationManager(){}

    /**
     * @brief newRequest
     * @return new a pointer to ClientRequests structure held in Communication Manager body
     */
    virtual pb::ClientRequest *newRequest( uint64_t &request_id ) = 0;

    /**
     * @brief socket
     * @return pointer to socket object
     */
    virtual QSharedPointer<ISocket> socket() const = 0;
public slots:
    virtual void sendUserRequest( std::shared_ptr<pb::UserReq> data) = 0;

signals:
    void connected();
    void disconnected();

    void error( CommunicationError error );

    void userRequestSent( RequestMetadata meta );
    void userResponse( ResponseMetadata meta, std::shared_ptr<pb::UserRes> data);
};
