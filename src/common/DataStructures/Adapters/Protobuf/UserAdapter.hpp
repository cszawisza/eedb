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

    data::UID get_id() const;
    void set_id(data::UID id);
    bool has_id() const;
    void clear_id();

    data::String *nickname();
    const data::String &get_nickname() const;
    void set_nickname(data::String);
    bool has_nickname() const;
    void clear_nickname();

    data::String *email();
    const data::String &get_email() const;
    void set_email(data::String);
    bool has_email() const;
    void clear_email();

    data::String *password();
    const data::String &get_password() const;
    void set_password(data::String);
    bool has_password() const;
    void clear_password();

    data::String *description();
    const data::String &get_description() const;
    void set_description(data::String);
    bool has_description() const;
    void clear_description();

    data::Bytes *avatar();
    const data::Bytes &get_avatar() const;
    void set_avatar(data::Bytes avatar);
    bool has_avatar() const;
    void clear_avatar();

    data::IAcl *acl();
    void assign_acl(data::IAcl *acl);
    bool has_acl() const;
    void clear_acl();

    data::String *address();
    const data::String &get_address() const;
    void set_address(data::String ads);
    bool has_address() const;
    void clear_address();

    data::String *phoneNumber();
    const data::String &get_phoneNumber() const;
    void set_phoneNumber(data::String number);
    bool has_phoneNumber() const;
    void clear_phoneNumber();
};

class ProtobufUserLoginAdapter: public data::requests::user::ILogin, public pb::UserReq_Login {
    // ILogin interface
public:
    data::Credentials *credentials();
    const data::Credentials &get_credentials() const;
    void set_credentials(data::Credentials);
    bool has_credentials() const;

    data::String *password();
    const data::String &get_password() const;
    void set_password(data::String pass);
    bool has_password() const;
};
