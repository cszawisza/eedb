#include "UserResponseAdapter.hpp"

#include "user.pb.h"

bool responses::User::has_add() const
{
    return m_data->has_add();
}

responses::user::ILogin * responses::User::login()
{
    Q_ASSERT(m_isMutable);
    m_login.reset(new responses::user::Login(m_data->mutable_login()) );
    return m_login.get();
}

const responses::user::ILogin &responses::User::get_login() const
{
    m_login.reset(new responses::user::Login(m_data->login()) );
    return *m_login;
}

bool responses::User::has_login() const
{
    return m_data->has_login();
}

responses::user::IGet * responses::User::get()
{
    Q_ASSERT(m_isMutable);
    m_get.reset(new responses::user::Get(m_data->mutable_get()));
    return m_get.get();
}

const responses::user::IGet &responses::User::get_get() const
{
    m_get.reset(new responses::user::Get(m_data->get()));
    return *m_get;
}

bool responses::User::has_get() const
{
    return m_data->has_get();
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

responses::user::Add::Add(protobuf::StdError *msg):
    m_data(msg),
    m_takeOvnership(false),
    m_isMutable(true)
{
}

responses::user::Add::Add(const protobuf::StdError &add):
    m_data(const_cast<protobuf::StdError*>(&add)),
    m_takeOvnership(false),
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
    return m_data->has_success() && m_data->success();
}

void responses::user::Add::set_successful(bool is_successful)
{
    Q_ASSERT(m_isMutable);
    m_data->set_success(is_successful);
}

bool responses::user::Add::is_not_successful() const
{
    return !is_successful();
}

void responses::user::Add::set_error(responses::user::IAdd::AddErrors code)
{
    Q_ASSERT(m_isMutable);

    if(code == AddError::Error_noError)
        m_data->set_success(true);

    m_data->set_error_code(code);
}

responses::user::IAdd::AddErrors responses::user::Add::get_error_code() const
{
    AddErrors err = QFlag((uint)m_data->error_code() );
    return err;
}

responses::user::Login::Login(protobuf::StdError *msg):
    m_takeOvnership(false),
    m_data(msg),
    m_isMutable(true)
{

}

responses::user::Login::Login(const protobuf::StdError &msg):
    m_takeOvnership(false),
    m_data(const_cast<protobuf::StdError*>(&msg)),
    m_isMutable(false)
{

}

bool responses::user::Login::is_successful() const
{
    return m_data->success();
}

void responses::user::Login::set_successful(bool is_successful)
{
    Q_ASSERT(m_isMutable);
    m_data->set_success(is_successful);
}

bool responses::user::Login::is_not_successful() const
{
    return !is_successful();
}

void responses::user::Login::set_error(responses::user::ILogin::LoginErrors code)
{
    Q_ASSERT(m_isMutable);
    m_data->set_error_code(code);
}

responses::user::ILogin::LoginErrors responses::user::Login::get_error_code() const
{
    auto code = m_data->error_code();
    return LoginErrors(code);
}


boost::optional<responses::user::Action> responses::User::stored_action() const
{
    ///FIXME
    switch (m_data->action_case()) {
    case protobuf::UserRes::kAdd:
       return user::Action_Add;
    default:
        break;
    }

    return boost::none;
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


responses::user::Get::Get(protobuf::StdError *msg):
    m_data(msg),
    m_takeOwnership(false),
    m_isMutable(true)
{

}

responses::user::Get::Get(const protobuf::StdError &msg):
    m_data(const_cast<protobuf::StdError*>(&msg)),
    m_takeOwnership(false),
    m_isMutable(false)
{

}
