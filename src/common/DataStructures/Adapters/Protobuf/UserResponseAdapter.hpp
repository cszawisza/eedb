#pragma once

#include "../../Interfaces/UserResponses.hpp"

namespace protobuf{
    class UserRes;
    class ServerResponse;
}

namespace responses{
namespace user{

class Add: public responses::user::IAdd{
    // IAdd interface
public:
    Add();
    Add(protobuf::UserRes *);
    ~Add();

    bool is_successful() const override;
    void set_successful( bool is_successful = true ) override;

    bool is_not_successful() const override;
    void set_error(AddErrors code) override;
    AddErrors get_error_code() const override;
private:
    protobuf::UserRes *m_data;
    bool m_takeOvnership = false;
};


class Login: public responses::user::ILogin{
    // IAdd interface
public:
    bool is_successful() const;
    void set_successful();

    bool is_not_successful() const;
    void set_error(LoginErrors code);
    LoginError get_error_code() const;
};

}

class User: public responses::IUser{
    // IUser interface
public:
    User();
    User(protobuf::UserRes *res);
    ~User();

    boost::optional<user::Action> stored_action() const;
    void clear_action() override;

    boost::optional<user::IAdd*> add() override;
    boost::optional<user::ILogin*> login() override;
    boost::optional<user::IGet*> get() override;

    bool has_add() const override;
    bool has_login() const override;
    bool has_get() const override;

    protobuf::UserRes *detachData();
private:
    protobuf::UserRes *m_data;
    bool m_takeOvnership = false;
};
}
