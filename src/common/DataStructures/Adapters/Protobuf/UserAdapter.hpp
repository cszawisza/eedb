#pragma once

#include "../../Interfaces/UserData.hpp"
#include "user.pb.h"

namespace data{
    class Acl;
}

class ProtobufAclAdapter;

class ProtobufUserAddAdapter: public data::requests::user::IAdd, public pb::UserReq_Add
{
public:
    ProtobufUserAddAdapter();

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

    data::IAcl *acl() override;
    void assign_acl(data::IAcl *acl) override;
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
};

class ProtobufUserLoginAdapter: public data::requests::user::ILogin, public pb::UserReq_Login {
    // ILogin interface
public:
    data::Credentials *credentials() override;
    const data::Credentials &get_credentials() const override;
    void set_credentials(data::Credentials) override;
    bool has_credentials() const override;

    data::String *password() override;
    const data::String &get_password() const override;
    void set_password(data::String) override;
    bool has_password() const override;
};

class ProtobufUserAdapter: public data::requests::IUser, public pb::UserReq{
public:
    void assign(data::requests::user::IAdd *add) override;
    void assign(data::requests::user::ILogin *login) override;

    data::requests::user::IAdd *add() override;
    bool has_add() const override;
    void clear_add() override;

    data::requests::user::ILogin *login() override;
    bool has_login() const override;
    void clear_login() override;
};
