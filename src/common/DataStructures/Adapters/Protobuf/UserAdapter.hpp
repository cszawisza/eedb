#pragma once
#include "../../Interfaces/UserData.hpp"

namespace data{
    class Acl;
}

namespace pb{
    class UserReq;
    class UserReq_Login;
    class UserReq_Add;
}

class ProtobufAclAdapter;

class ProtobufUserAddAdapter: public data::requests::user::IAdd
{
public:
    ProtobufUserAddAdapter();
    ProtobufUserAddAdapter( pb::UserReq_Add * );
    ~ProtobufUserAddAdapter();

    data::UID get_id() const override;
    void set_id(data::UID id) override;
    bool has_id() const override;
    void clear_id() override;

    data::String *nickname() override;
    const data::String &get_nickname() const override;
    void set_nickname(data::String) override;
    bool has_nickname() const override;
    void clear_nickname() override;

    data::String *email() override;
    const data::String &get_email() const override;
    void set_email(data::String) override;
    bool has_email() const override;
    void clear_email() override;

    data::String *password() override;
    const data::String &get_password() const override;
    void set_password(data::String) override;
    bool has_password() const override;
    void clear_password() override;

    data::String *description() override;
    const data::String &get_description() const override;
    void set_description(data::String) override;
    bool has_description() const override;
    void clear_description() override;

    data::Bytes *avatar() override;
    const data::Bytes &get_avatar() const override;
    void set_avatar(data::Bytes avatar) override;
    bool has_avatar() const override;
    void clear_avatar() override;

    std::shared_ptr<data::IAcl> acl() override;
    void assign_acl(std::shared_ptr<data::IAcl> acl) override;
    bool has_acl() const override;
    void clear_acl() override;

    data::String *address() override;
    const data::String &get_address() const override;
    void set_address(data::String ads) override;
    bool has_address() const override;
    void clear_address() override;

    data::String *phoneNumber() override;
    const data::String &get_phoneNumber() const override;
    void set_phoneNumber(data::String number) override;
    bool has_phoneNumber() const override;
    void clear_phoneNumber() override;

    pb::UserReq_Add *detachData();
private:
    pb::UserReq_Add *m_data;
    bool take_ovnership = false;
};

class ProtobufUserLoginAdapter: public data::requests::user::ILogin {
    // ILogin interface
public:
    ProtobufUserLoginAdapter();
    ProtobufUserLoginAdapter( pb::UserReq_Login *login_msg );
    ~ProtobufUserLoginAdapter();

    data::Credentials *credentials() override;
    const data::Credentials &get_credentials() const override;
    void set_credentials(data::Credentials) override;
    bool has_credentials() const override;

    data::String *password() override;
    const data::String &get_password() const override;
    void set_password(data::String) override;
    bool has_password() const override;

    pb::UserReq_Login *detachData();
private:
    bool m_takeOvnership = false;
    pb::UserReq_Login *m_data;
};

class ProtobufUserAdapter: public data::requests::IUser {
public:
    ProtobufUserAdapter();
    ProtobufUserAdapter( pb::UserReq *req );

    ~ProtobufUserAdapter();
//    std::shared_ptr<data::requests::user::IAdd> detach() override;
    void assign(std::shared_ptr<data::requests::user::IAdd> add) override;
    void assign(std::shared_ptr<data::requests::user::ILogin> login) override;

    std::shared_ptr<data::requests::user::IAdd> add() override;
    bool has_add() const override;
    void clear_add() override;

    std::shared_ptr<data::requests::user::ILogin> login() override;
    bool has_login() const override;
    void clear_login() override;

private:
    pb::UserReq *m_data;
    bool take_ovnership = false;
};
