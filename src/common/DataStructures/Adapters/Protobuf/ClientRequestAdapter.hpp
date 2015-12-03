#pragma once

#include "../../Interfaces/ClientRequest.hpp"
#include "message_conteiner.pb.h"

#include <vector>
#include <memory>

namespace data{
namespace requests{
    class IUser;
}
}

class ProtobufClientRequestAdapter : public data::IClientRequest, public pb::ClientRequest {
public:
    int get_requestId() const;
    data::requests::IUser *user();
    void assign_user(data::requests::IUser *ur);
    bool has_user() const;
    void clear_user();
};

class ProtobufClientRequestsAdapter : public data::IClientRequests, public pb::ClientRequests {
    // IClientRequests interface
public:
    data::IClientRequest *newClientRequest();
    int requests_size() const;

    void form();
private:
    std::vector<ProtobufClientRequestAdapter*> m_requests;
};
