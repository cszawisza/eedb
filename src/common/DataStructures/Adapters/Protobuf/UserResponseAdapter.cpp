#include "UserResponseAdapter.hpp"

#include "user.pb.h"

bool responses::User::has_add() const
{
    ///IMPLEMENT
}

boost::optional<responses::user::ILogin *> responses::User::login()
{
    ///IMPLEMENT
}

bool responses::User::has_login() const
{
    ///IMPLEMENT
}

boost::optional<responses::user::IGet *> responses::User::get()
{
    ///IMPLEMENT
}

bool responses::User::has_get() const
{
    ///IMPLEMENT
}

void responses::User::clear_action()
{
    m_data->Clear();
}

protobuf::UserRes *responses::User::detachData()
{
    m_takeOvnership = false;
    return m_data;
}

responses::User::User():
    m_data(new protobuf::UserRes), m_takeOvnership(true)
{
}

responses::User::User(protobuf::UserRes *res):
    m_data(res), m_takeOvnership(false)
{
}

responses::User::~User()
{
    if(m_takeOvnership){
        delete m_data;
    }
}

responses::user::Add::Add():
    m_data(new protobuf::UserRes(protobuf::UserRes::default_instance())), m_takeOvnership(true)
{
}

responses::user::Add::Add(protobuf::UserRes *msg):
    m_data( msg ), m_takeOvnership(false)
{
}

responses::user::Add::~Add()
{
    if(m_takeOvnership)
        delete m_data;
}

bool responses::user::Add::is_successful() const
{
    return m_data->has_has_error() ? !m_data->has_error() : true;
}

void responses::user::Add::set_successful(bool is_successful)
{
    if(is_successful){
        m_data->clear_error_code();
        m_data->clear_has_error();
    }
    else{
        m_data->clear_error_code();
        m_data->set_has_error(true);
    }
}

bool responses::user::Add::is_not_successful() const
{
    return !is_successful();
}

void responses::user::Add::set_error(responses::user::IAdd::AddErrors code)
{
    if(code == AddError::Error_noError)
        m_data->set_has_error(false);
    m_data->set_error_code(code);
}

responses::user::IAdd::AddErrors responses::user::Add::get_error_code() const
{
    AddErrors err = QFlag((uint)m_data->error_code() );
    return err;
}

bool responses::user::Login::is_successful() const
{
    ///IMPLEMENT
}

void responses::user::Login::set_successful()
{
    ///IMPLEMENT
}

bool responses::user::Login::is_not_successful() const
{
    ///IMPLEMENT
}

void responses::user::Login::set_error(responses::user::ILogin::LoginErrors code)
{
    ///IMPLEMENT

}

responses::user::ILogin::LoginError responses::user::Login::get_error_code() const
{
    ///IMPLEMENT

}


boost::optional<responses::user::Action> responses::User::stored_action() const
{
    ///IMPLEMENT
}

boost::optional<responses::user::IAdd *> responses::User::add()
{
    ///IMPLEMENT

}
