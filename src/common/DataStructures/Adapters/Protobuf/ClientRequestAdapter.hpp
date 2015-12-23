#pragma once

#include "../../Interfaces/ClientRequest.hpp"

namespace pb{
    class ClientRequest;
}

namespace requests{
class IUser;
class ProtobufUserAdapter;
}


class ProtobufClientRequestAdapter : public IClientRequest {
public:
    ProtobufClientRequestAdapter();
    ProtobufClientRequestAdapter(pb::ClientRequest *req);
    ~ProtobufClientRequestAdapter();

    int get_requestId() const;

    requests::IUser* user();
    void assign_user(requests::IUser *ur);
    bool has_user() const;
    void clear_user();

    pb::ClientRequest *rawPointer() const;
private:
    pb::ClientRequest *m_data;
    bool m_takeOvnership = false;
    mutable requests::ProtobufUserAdapter *m_userreq;
};

