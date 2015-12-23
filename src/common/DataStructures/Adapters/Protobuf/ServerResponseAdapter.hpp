#pragma once

#include "../../Interfaces/ServerResponse.hpp"

namespace pb{
    class ServerResponse;
}

namespace data{
//namespace requests{
//    class IUser;
//}
}

class ProtobufServerResponseAdapter : public IServerResponse {
public:
    ProtobufServerResponseAdapter();
    ProtobufServerResponseAdapter(pb::ServerResponse *req);
    ~ProtobufServerResponseAdapter();

    void set_response_id( uint64_t id );
    void set_in_response_to(uint64_t id);
    void set_response_code(int code);
//    int get_requestId() const;

    requests::IUser* user();
    void assign_user(requests::IUser *ur);
    bool has_user() const;
    void clear_user();

    pb::ServerResponse *rawPointer() const;
private:
    bool m_takeOvnership = false;
    pb::ServerResponse *m_data;
};

