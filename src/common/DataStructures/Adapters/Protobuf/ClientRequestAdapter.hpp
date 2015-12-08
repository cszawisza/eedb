#pragma once

#include "../../Interfaces/ClientRequest.hpp"

namespace pb{
    class ClientRequest;
}

namespace data{
namespace requests{
    class IUser;
}
}

class ProtobufClientRequestAdapter : public data::IClientRequest {
public:
    ProtobufClientRequestAdapter();
    ProtobufClientRequestAdapter(pb::ClientRequest *req);
    ~ProtobufClientRequestAdapter();

    int get_requestId() const;

    std::unique_ptr<data::requests::IUser> user();
    void assign_user(data::requests::IUser *ur);
    bool has_user() const;
    void clear_user();

    pb::ClientRequest *rawPointer() const;
private:
    bool m_takeOvnership = false;
    pb::ClientRequest *m_data;
};

