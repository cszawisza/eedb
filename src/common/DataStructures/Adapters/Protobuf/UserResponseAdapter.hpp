#pragma once

#include "../../Interfaces/UserResponses.hpp"

namespace protobuf{
    class StdError;
    class UserRes;
    class ServerResponse;
}

namespace responses{
namespace user{

class Add: public responses::user::IAdd{
    // IAdd interface
public:
    Add(protobuf::StdError *);
    Add( const protobuf::StdError &add);

    ~Add();

    bool is_successful() const override;
    void set_successful( bool is_successful = true ) override;

    bool is_not_successful() const override;
    void set_error(AddErrors code) override;
    AddErrors get_error_code() const override;
private:
    protobuf::StdError *m_data;
    bool m_takeOvnership = false;
    bool m_isMutable = true;
};

class Login: public responses::user::ILogin{
    // IAdd interface
public:
    Login( protobuf::StdError* msg);
    Login(const protobuf::StdError &msg);
    bool is_successful() const override;
    void set_successful(bool is_successful = true) override;

    bool is_not_successful() const;
    void set_error(LoginErrors code);
    LoginErrors get_error_code() const;
private:
    bool m_takeOvnership;
    protobuf::StdError *m_data;
    bool m_isMutable;
};

class Get: public responses::user::IGet{
public:
    Get( protobuf::StdError *msg );
    Get( const protobuf::StdError &msg );

private:
    protobuf::StdError *m_data;
    bool m_takeOwnership;
    bool m_isMutable;
};

}

class User: public responses::IUser{
    // IUser interface
public:
    User();
    User(protobuf::UserRes *res);
    User( const protobuf::UserRes & res );
    ~User();

    boost::optional<user::Action> stored_action() const;
    void clear_action() override;

    user::IAdd* add();
    const user::IAdd& get_add() const;
    bool has_add() const override;

    user::ILogin *login();
    const user::ILogin& get_login() const;
    bool has_login() const override;

    user::IGet *get();
    const user::IGet& get_get() const;
    bool has_get() const override;

    protobuf::UserRes *detachData();
private:
    bool m_takeOvnership = false;
    protobuf::UserRes *m_data;
    bool m_isMutable = true;

    mutable std::shared_ptr<user::IAdd> m_add;
    mutable std::shared_ptr<user::IGet> m_get;
    mutable std::shared_ptr<user::ILogin> m_login;
};
}
