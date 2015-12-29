#pragma once

#include "../../Interfaces/ServerResponse.hpp"

namespace protobuf{
    class ServerResponse;
}

namespace responses{
    class IUser;
}

class ResponseSerializer;

class ServerResponse : public IServerResponse {
public:
    ServerResponse();
    ServerResponse(protobuf::ServerResponse *req);
    ~ServerResponse();

    void set_response_id( uint64_t id );
    void set_in_response_to(uint64_t id);
    void set_response_code(int code);
//    int get_requestId() const;

    responses::IUser* user();
    void assign(responses::IUser *ur);
    bool has_user() const;
    void clear_user();

    protobuf::ServerResponse *rawPointer() const;
private:
    bool m_takeOvnership = false;
    protobuf::ServerResponse *m_data;
    mutable responses::IUser *m_user;


    // IServerResponse interface
public:
    void parse(const QByteArray &data);
    QByteArray serialize() const;
};

