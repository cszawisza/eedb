#pragma once
#include "../../Interfaces/UserRequests.hpp"

class IAcl;

namespace pb{
    class UserReq;
    class UserReq_Login;
    class UserReq_Add;
    class UserReq_Get;
}

class ProtobufAclAdapter;
class ProtobufAuthorizationDataAdapter;

namespace requests{
namespace user{
class ICriterion;


class ProtobufCriterionAdapter: public requests::user::ICriterion{

};

class ProtobufUserAddAdapter: public requests::user::IAdd
{
public:
    ProtobufUserAddAdapter();
    ProtobufUserAddAdapter( pb::UserReq_Add * );
    ~ProtobufUserAddAdapter();

    UID get_id() const override;
    void set_id(UID id) override;
    bool has_id() const override;
    void clear_id() override;

    String *nickname() override;
    const String &get_nickname() const override;
    void set_nickname(String) override;
    bool has_nickname() const override;
    void clear_nickname() override;

    String *email() override;
    const String &get_email() const override;
    void set_email(String) override;
    bool has_email() const override;
    void clear_email() override;

    String *password() override;
    const String &get_password() const override;
    void set_password(String) override;
    bool has_password() const override;
    void clear_password() override;

    String *description() override;
    const String &get_description() const override;
    void set_description(String) override;
    bool has_description() const override;
    void clear_description() override;

    Bytes *avatar() override;
    const Bytes &get_avatar() const override;
    void set_avatar(Bytes avatar) override;
    bool has_avatar() const override;
    void clear_avatar() override;

    IAcl* acl() override;
    const IAcl &get_acl() const override;
    void assign_acl(IAcl *acl) override;
    bool has_acl() const override;
    void clear_acl() override;

    String *address() override;
    const String &get_address() const override;
    void set_address(String ads) override;
    bool has_address() const override;
    void clear_address() override;

    String *phoneNumber() override;
    const String &get_phoneNumber() const override;
    void set_phoneNumber(String number) override;
    bool has_phoneNumber() const override;
    void clear_phoneNumber() override;

    pb::UserReq_Add *detachData();
private:
    pb::UserReq_Add *m_data;
    bool take_ovnership = false;
    mutable ProtobufAclAdapter *m_adp;
};

class ProtobufUserLoginAdapter: public requests::user::ILogin {
    // ILogin interface
public:
    ProtobufUserLoginAdapter();
    ProtobufUserLoginAdapter( pb::UserReq_Login *login_msg );
    ~ProtobufUserLoginAdapter();

    IAuthorizationData* credentials() override;
    void assign_credentials( IAuthorizationData* cred ) override;
    bool has_credentials() const override;

    String *password() override;
    const String &get_password() const override;
    void set_password(String) override;
    bool has_password() const override;

    pb::UserReq_Login *detachData();
private:
    pb::UserReq_Login *m_data;
    bool m_takeOvnership = false;

    mutable ProtobufAuthorizationDataAdapter* m_auth;
};

class ProtobufUserGetAdapter: public requests::user::IGet{
    // IGet interface
public:
    ProtobufUserGetAdapter();
    ProtobufUserGetAdapter( pb::UserReq_Get *get );
    ~ProtobufUserGetAdapter();

    bool has_requestedUid() const override;
    void request_uid(bool request = true ) override;

    bool has_requestedAddress() const override;
    void request_address(bool request = true ) override;

    bool has_requestedPhoneNumber() const override;
    void request_phoneNumber(bool request = true ) override;

    bool has_requestedDescription() const override;
    void request_description(bool request = true ) override;

    bool has_requestedAvatar() const override;
    void request_avatar(bool request = true ) override;

    bool has_requestedAcl() const override;
    void request_acl(bool request = true ) override;

    requests::user::ICriterion *criteria() override;
    void set_requestCriterion(ICriterion*) override;
    const ICriterion& getCriteria() const override;

    pb::UserReq_Get *detachData();
private:
    pb::UserReq_Get * m_data;
    bool m_takeOvnership = false;
};

}

class ProtobufUserAdapter: public requests::IUser {
public:
    ProtobufUserAdapter();
    ProtobufUserAdapter( pb::UserReq *req );

    ~ProtobufUserAdapter();
    void assign(requests::user::IAdd *add) override;
    void assign(requests::user::ILogin *login) override;
    void assign(requests::user::IGet *get) override;

    requests::user::IAdd* add() override;
    bool has_add() const override;
    void clear_add() override;

    requests::user::ILogin* login() override;
    bool has_login() const override;
    void clear_login() override;

    requests::user::IGet* get() override;
    bool has_get() const override;
    void clear_get() override;

    pb::UserReq *detachData();
private:
    pb::UserReq *m_data;
    bool m_takeOvnership = false;

    mutable requests::user::IAdd *m_add;
    mutable requests::user::ILogin *m_login;
    mutable requests::user::IGet *m_get;
};


}
