#pragma once

#include "../../Interfaces/ServerResponse.hpp"

namespace protobuf{
    class ServerResponse;
}

namespace responses{
    class IUser;
    class ICategory;
}

class ResponseSerializer;

class ServerResponse : public IServerResponse {
public:
    ServerResponse();
    ServerResponse(protobuf::ServerResponse *req);
    ~ServerResponse();

    void set_response_id( uint64_t id ) override;
    void set_in_response_to(uint64_t id) override;
    void set_response_code(ResponseFlags code) override;
//    int get_requestId() const;

    responses::IUser* user() override;
    void assign(responses::IUser *ur) override;
    bool has_user() const override;
    void clear_user() override;

    responses::ICategory* category() override;
    void assign(responses::ICategory *ur) override;
    bool has_category() const override;
    void clear_category() override;

    protobuf::ServerResponse *rawPointer() const;
private:
    bool m_takeOvnership = false;
    protobuf::ServerResponse *m_data;
    mutable responses::IUser *m_user;


    // IServerResponse interface
public:
    void parse(const QByteArray &data) override;
    QByteArray serialize() const override;
};

