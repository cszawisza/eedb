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
    void set_error(LoginError code);
    LoginError get_error_code() const;
};

}

class User: public responses::IUser{
    // IUser interface
public:
    User();
    User(protobuf::UserRes *res);
    ~User();


    user::IAdd *add() override;
    void assign( user::IAdd* msg);
    bool has_add() const override;
    void clear_add() override;

    user::ILogin *login() override;
    void assign( user::ILogin* msg);
    bool has_login() const override;
    void clear_login() override;

    user::IGet *get() override;
    void assign( user::IGet* msg);
    bool has_get() const override;
    void clear_get() override;

    protobuf::UserRes *detachData();
private:
    protobuf::UserRes *m_data;
    bool m_takeOvnership = false;
//    protobuf::UserRes *m_userres;
//    protobuf::UserRes *m_userres;
//    protobuf::UserRes *m_userres;
};
}
