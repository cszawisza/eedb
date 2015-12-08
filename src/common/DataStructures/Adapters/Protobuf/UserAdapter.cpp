#include "UserAdapter.hpp"
#include "AclAdapter.hpp"
#include "user.pb.h"
#include "../../Interfaces/AclData.hpp"

using namespace data;

ProtobufUserAddAdapter::ProtobufUserAddAdapter():
    m_data(new pb::UserReq_Add()), take_ovnership(true)
{
}

ProtobufUserAddAdapter::ProtobufUserAddAdapter(pb::UserReq_Add *msg):
    m_data(msg)
{
}

ProtobufUserAddAdapter::~ProtobufUserAddAdapter()
{
    if(take_ovnership)
        delete m_data;
}

UID ProtobufUserAddAdapter::get_id() const
{
    return m_data->basic().id();
}

void ProtobufUserAddAdapter::set_id(UID id)
{
    m_data->mutable_basic()->set_id( id );
}

bool ProtobufUserAddAdapter::has_id() const
{
    return m_data->basic().has_id();
}

void ProtobufUserAddAdapter::clear_id()
{
    m_data->mutable_basic()->clear_id();
}

String *ProtobufUserAddAdapter::nickname()
{
    return m_data->mutable_basic()->mutable_nickname();
}

const String &ProtobufUserAddAdapter::get_nickname() const
{
    return m_data->basic().nickname();
}

void ProtobufUserAddAdapter::set_nickname(String nick)
{
    m_data->mutable_basic()->set_nickname( nick );
}

bool ProtobufUserAddAdapter::has_nickname() const
{
    return m_data->basic().has_nickname();
}

void ProtobufUserAddAdapter::clear_nickname()
{
    m_data->mutable_basic()->clear_nickname();
}

String *ProtobufUserAddAdapter::email()
{
    return m_data->mutable_basic()->mutable_email();
}

const String &ProtobufUserAddAdapter::get_email() const
{
    return m_data->basic().email();
}

void ProtobufUserAddAdapter::set_email(String email)
{
    m_data->mutable_basic()->set_email( email );
}

bool ProtobufUserAddAdapter::has_email() const
{
    return m_data->basic().has_email();
}

void ProtobufUserAddAdapter::clear_email()
{
    m_data->mutable_basic()->clear_email();
}

String *ProtobufUserAddAdapter::password()
{
    return m_data->mutable_password();
}

const String &ProtobufUserAddAdapter::get_password() const
{
    return m_data->password();
}

void ProtobufUserAddAdapter::set_password(String pass)
{
    m_data->set_password( pass );
}

bool ProtobufUserAddAdapter::has_password() const
{
    return m_data->has_password();
}

void ProtobufUserAddAdapter::clear_password()
{
    m_data->clear_password();
}

String *ProtobufUserAddAdapter::description()
{
    return m_data->mutable_basic()->mutable_description();
}

const String &ProtobufUserAddAdapter::get_description() const
{
    return m_data->basic().description();
}

void ProtobufUserAddAdapter::set_description(String desc)
{
    m_data->mutable_basic()->set_description( desc );
}

bool ProtobufUserAddAdapter::has_description() const
{
    return m_data->basic().has_description();
}

void ProtobufUserAddAdapter::clear_description()
{
    m_data->mutable_basic()->clear_description();
}

Bytes *ProtobufUserAddAdapter::avatar()
{
    return m_data->mutable_basic()->mutable_avatar();
}

const Bytes &ProtobufUserAddAdapter::get_avatar() const
{
    return m_data->basic().avatar();
}

void ProtobufUserAddAdapter::set_avatar(Bytes avatar)
{
    m_data-> mutable_basic()->set_avatar(move(avatar));
}

bool ProtobufUserAddAdapter::has_avatar() const
{
    return m_data->basic().has_avatar();
}

void ProtobufUserAddAdapter::clear_avatar()
{
    m_data->mutable_basic()->clear_avatar();
}

std::shared_ptr<IAcl> ProtobufUserAddAdapter::acl()
{
    return std::make_shared<ProtobufAclAdapter>(m_data->mutable_acl());
}

void ProtobufUserAddAdapter::assign_acl(std::shared_ptr<IAcl> acl)
{
    m_data->set_allocated_acl( std::dynamic_pointer_cast<ProtobufAclAdapter>(acl)->detachData() );
}

bool ProtobufUserAddAdapter::has_acl() const
{
    return m_data->has_acl();
}

void ProtobufUserAddAdapter::clear_acl()
{
    m_data->clear_acl();
}

String *ProtobufUserAddAdapter::address()
{
    return m_data->mutable_details()->mutable_address();
}

const String &ProtobufUserAddAdapter::get_address() const
{
    return m_data->details().address();
}

void ProtobufUserAddAdapter::set_address(String ads)
{
    m_data->mutable_details()->set_address(std::move(ads));
}

bool ProtobufUserAddAdapter::has_address() const
{
    return m_data->details().has_address();
}

void ProtobufUserAddAdapter::clear_address()
{
    m_data->mutable_details()->clear_address();
}

String *ProtobufUserAddAdapter::phoneNumber()
{
    return m_data->mutable_details()->mutable_address();
}

const String &ProtobufUserAddAdapter::get_phoneNumber() const
{
    return m_data->details().phone_number();
}

void ProtobufUserAddAdapter::set_phoneNumber(String number)
{
    m_data->mutable_details()->set_phone_number(std::move(number));
}

bool ProtobufUserAddAdapter::has_phoneNumber() const
{
    return m_data->details().has_phone_number();
}

void ProtobufUserAddAdapter::clear_phoneNumber()
{
    m_data->mutable_details()->mutable_phone_number();
}

pb::UserReq_Add *ProtobufUserAddAdapter::detachData()
{
    take_ovnership = false;
    return m_data;
}

ProtobufUserLoginAdapter::ProtobufUserLoginAdapter():
    m_data(new pb::UserReq_Login() ), m_takeOvnership(true)
{
}

ProtobufUserLoginAdapter::ProtobufUserLoginAdapter(pb::UserReq_Login *login_msg):
    m_data(login_msg){
}

ProtobufUserLoginAdapter::~ProtobufUserLoginAdapter()
{
    if(m_takeOvnership)
        delete m_data;
}

Credentials *ProtobufUserLoginAdapter::credentials()
{
}

const Credentials &ProtobufUserLoginAdapter::get_credentials() const
{
}

void ProtobufUserLoginAdapter::set_credentials(Credentials)
{
}

bool ProtobufUserLoginAdapter::has_credentials() const
{
}

String *ProtobufUserLoginAdapter::password()
{
    return m_data->mutable_password();
}

const String &ProtobufUserLoginAdapter::get_password() const
{
    return m_data->password();
}

void ProtobufUserLoginAdapter::set_password(String pass)
{
    m_data->set_password(move(pass));
}

bool ProtobufUserLoginAdapter::has_password() const
{
    return m_data->has_password();
}

pb::UserReq_Login *ProtobufUserLoginAdapter::detachData()
{
    m_takeOvnership = false;
    return m_data;
}


std::shared_ptr<requests::user::IAdd> ProtobufUserAdapter::add()
{
    return std::make_shared<ProtobufUserAddAdapter>( m_data->mutable_add() );
}

ProtobufUserAdapter::ProtobufUserAdapter():
    m_data(new pb::UserReq), take_ovnership(true)
{
}

ProtobufUserAdapter::ProtobufUserAdapter(pb::UserReq *req):
    m_data(req)
{
}

ProtobufUserAdapter::~ProtobufUserAdapter()
{
    if(take_ovnership)
        delete m_data;
}

void ProtobufUserAdapter::assign(std::shared_ptr<requests::user::IAdd> add)
{
    m_data->set_allocated_add( std::dynamic_pointer_cast<ProtobufUserAddAdapter>(add)->detachData() );
}

bool ProtobufUserAdapter::has_add() const
{
    return m_data->has_add();
}

void ProtobufUserAdapter::clear_add()
{
    m_data->clear_add();
}

std::shared_ptr<requests::user::ILogin> ProtobufUserAdapter::login()
{
    return std::make_shared<ProtobufUserLoginAdapter>(m_data->mutable_login());
}

void ProtobufUserAdapter::assign(std::shared_ptr<requests::user::ILogin> login)
{
    m_data->set_allocated_login( std::dynamic_pointer_cast<ProtobufUserLoginAdapter>(login)->detachData() );
}

bool ProtobufUserAdapter::has_login() const
{
    return m_data->has_login();
}

void ProtobufUserAdapter::clear_login()
{
    m_data->clear_login();
}
