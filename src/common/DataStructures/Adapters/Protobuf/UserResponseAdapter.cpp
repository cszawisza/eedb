#include "UserResponseAdapter.hpp"

#include "user.pb.h"

bool responses::User::has_add() const
{
    ///IMPLEMENT
}

responses::user::ILogin * responses::User::login()
{
    Q_ASSERT(m_isMutable);
    ///IMPLEMENT
}

const responses::user::ILogin &responses::User::get_login() const
{
    ///IMPLEMENT
}

bool responses::User::has_login() const
{
    ///IMPLEMENT
}

responses::user::IGet * responses::User::get()
{
    Q_ASSERT(m_isMutable);
    ///IMPLEMENT
}

const responses::user::IGet &responses::User::get_get() const
{
    ///IMPLEMENT
}

bool responses::User::has_get() const
{
    ///IMPLEMENT
}

void responses::User::clear_action()
{
    Q_ASSERT(m_isMutable);
    m_data->Clear();
}

protobuf::UserRes *responses::User::detachData()
{
    Q_ASSERT(m_isMutable);
    m_takeOvnership = false;
    return m_data;
}

responses::User::User():
    m_takeOvnership(true),
    m_data(new protobuf::UserRes),
    m_isMutable(true)
{
}

responses::User::User(protobuf::UserRes *res):
    m_takeOvnership(false),
    m_data(res),
    m_isMutable(true)
{
}

responses::User::User(const protobuf::UserRes &res):
    m_takeOvnership(false),
    m_data(const_cast<protobuf::UserRes *>(&res)),
    m_isMutable(true)
{

}

responses::User::~User()
{
    if(m_takeOvnership){
        delete m_data;
    }
}

responses::user::Add::Add():
    m_takeOvnership(true),
    m_data(new protobuf::UserRes_Add(protobuf::UserRes_Add::default_instance())),
    m_isMutable(true)
{

}

responses::user::Add::Add(protobuf::UserRes_Add *msg):
    m_takeOvnership(false),
    m_data(msg),
    m_isMutable(true)
{
}

responses::user::Add::Add(const protobuf::UserRes_Add &add):
    m_takeOvnership(false),
    m_data(const_cast<protobuf::UserRes_Add *>(&add)),
    m_isMutable(false)
{

}

responses::user::Add::~Add()
{
    if(m_takeOvnership)
        delete m_data;
}

bool responses::user::Add::is_successful() const
{
    return m_data->has_succes() && m_data->succes();
}

void responses::user::Add::set_successful(bool is_successful)
{
    Q_ASSERT(m_isMutable);
//    if(is_successful){
        m_data->set_succes(is_successful);
//        m_data->clear_error_code();
//        m_data->clear_has_error();
//    }
//    else{
//        m_data->clear_succes();
//        m_data->set_has_error(true);
//    }
}

bool responses::user::Add::is_not_successful() const
{
    return !is_successful();
}

void responses::user::Add::set_error(responses::user::IAdd::AddErrors code)
{
    Q_ASSERT(m_isMutable);

    if(code == AddError::Error_noError)
        m_data->set_succes(true);

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

responses::user::IAdd * responses::User::add()
{
    Q_ASSERT(m_isMutable);
    m_add.reset(new responses::user::Add(m_data->mutable_add()));
    return m_add.get();
}

const responses::user::IAdd &responses::User::get_add() const
{
    m_add.reset(new responses::user::Add(m_data->add()));
    return *m_add;
}
