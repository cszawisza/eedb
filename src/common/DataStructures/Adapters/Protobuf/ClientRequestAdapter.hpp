#pragma once

#include "../../Interfaces/ClientRequest.hpp"

#include <memory>

namespace protobuf{
    class ClientRequest;
}

namespace requests{
class IUser;
class User;
}

class ClientRequest : public IClientRequest {
public:
    ClientRequest();
    ClientRequest(protobuf::ClientRequest *req);
    ~ClientRequest();

    int get_requestId() const;

    requests::IUser* user() override;
    const requests::IUser &get_user() const override;
    bool has_user() const override;
    void clear_user() override;

    requests::ICategory * category() override;
    const requests::ICategory &get_category() const override;
    bool has_category() const override;
    void clear_category() override;

//    void assign(requests::IUser *ur) override;
//    void assign(requests::ICategory *ur) override;

    protobuf::ClientRequest *rawPointer() const;
private:
    protobuf::ClientRequest *m_data;
    bool m_takeOvnership = false;
    mutable requests::User *m_userreq;

    // IClientRequest interface
public:
    void parse(const QByteArray &data);
    QByteArray serialize() const;

};

