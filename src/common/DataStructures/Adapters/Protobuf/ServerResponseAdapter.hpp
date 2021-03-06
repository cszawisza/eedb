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
    void Clear() override;

    boost::optional<ActionTypeId> message_type() const override;

    void set_response_id( uint64_t id ) override;
    UID response_id() const override;

    void set_in_response_to(uint64_t id) override;
    UID in_response_to() const override;

    void set_response_code(ResponseFlags code) override;
    ResponseFlags response_code() const override;

    responses::IUser* user() override;
    const responses::IUser &get_user() const;
    bool has_user() const override;
    void clear_user() override;

    responses::ICategory* category() override;
    const responses::ICategory &get_category() const;
    bool has_category() const override;
    void clear_category() override;

    protobuf::ServerResponse *rawPointer() const;
private:
    protobuf::ServerResponse *m_data;
    bool m_takeOvnership = false;
    mutable std::shared_ptr<responses::IUser> m_user;
    mutable std::shared_ptr<responses::ICategory> m_category;

    // IServerResponse interface
public:
    void parse(const QByteArray &data) override;
    QByteArray serialize() const override;
    mutable QByteArray m_buffer;
};

