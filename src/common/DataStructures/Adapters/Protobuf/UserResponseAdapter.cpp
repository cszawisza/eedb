#include "UserResponseAdapter.hpp"

#include "user.pb.h"
#include "DefinedActions.hpp"

bool responses::User::has_add() const
{
    return m_data->has_add();
}

responses::user::ILogin * responses::User::login()
{
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
    m_data->Clear();
}

protobuf::UserRes *responses::User::detachData()
{
    m_takeOvnership = false;
    return m_data;
}

responses::User::User():
    m_data(new protobuf::UserRes),
    m_takeOvnership(true)
{
}

responses::User::User(protobuf::UserRes *res):
    m_data(res),
    m_takeOvnership(false)
{
}

responses::User::User(const protobuf::UserRes &res):
    m_data(const_cast<protobuf::UserRes *>(&res)),
    m_takeOvnership(false)
{

}

responses::User::~User()
{
    if(m_takeOvnership)
        delete m_data;
}

boost::optional<ActionId> responses::User::action_type() const
{
    using namespace actions::user;
    using namespace protobuf;
    switch (m_data->action_case()) {
    case UserRes::kAdd:
       return ActionAdd;
    case UserRes::kLogin:
        return ActionLogin;
    case UserRes::kGet:
        return ActionGet;
    default:
        break;
    }

    return boost::none;
}

responses::user::Add::Add(protobuf::StdError *msg):
    m_data(msg),
    m_takeOvnership(false)
{
}

responses::user::Add::Add(const protobuf::StdError &add):
    m_data(const_cast<protobuf::StdError*>(&add)),
    m_takeOvnership(false)
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
    m_data->set_success(is_successful);
}

bool responses::user::Add::is_not_successful() const
{
    return !is_successful();
}

void responses::user::Add::set_error(responses::user::IAdd::AddErrors code)
{
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
    m_data(msg),
    m_takeOvnership(false)
{

}

responses::user::Login::Login(const protobuf::StdError &msg):
    m_data(const_cast<protobuf::StdError*>(&msg)),
    m_takeOvnership(false)
{

}

bool responses::user::Login::is_successful() const
{
    return m_data->success();
}

void responses::user::Login::set_successful(bool is_successful)
{
    m_data->set_success(is_successful);
}

bool responses::user::Login::is_not_successful() const
{
    return !is_successful();
}

void responses::user::Login::set_error(responses::user::ILogin::LoginErrors code)
{
    m_data->set_error_code(code);
}

responses::user::ILogin::LoginErrors responses::user::Login::get_error_code() const
{
    auto code = m_data->error_code();
    return LoginErrors(code);
}

responses::user::IAdd * responses::User::add()
{
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
    m_takeOwnership(false)
{

}

responses::user::Get::Get(const protobuf::StdError &msg):
    m_data(const_cast<protobuf::StdError*>(&msg)),
    m_takeOwnership(false)
{

}
