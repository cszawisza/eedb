#include "UserRequestAdapter.hpp"
#include "AclAdapter.hpp"
#include "user.pb.h"

#include "CommonDataStructuresAdapter.hpp"

#include "../../Interfaces/AclData.hpp"
#include "../../Interfaces/UserRequests.hpp"

using namespace data;

namespace requests {
namespace user{

Add::Add():
    m_data(new protobuf::UserReq_Add()), take_ovnership(true), m_adp( nullptr )
{
}

Add::Add(protobuf::UserReq_Add *msg):
    m_data(msg), m_adp( nullptr )
{
}

Add::~Add()
{
    if(take_ovnership){
        delete m_data;
    }
    if(m_adp)
        delete m_adp;
}

UID Add::get_id() const
{
    return m_data->basic().id();
}

void Add::set_id(UID id)
{
    m_data->mutable_basic()->set_id( id );
}

bool Add::has_id() const
{
    return m_data->basic().has_id();
}

void Add::clear_id()
{
    m_data->mutable_basic()->clear_id();
}

String *Add::nickname()
{
    return m_data->mutable_basic()->mutable_nickname();
}

const String &Add::get_nickname() const
{
    return m_data->basic().nickname();
}

void Add::set_nickname(String nick)
{
    m_data->mutable_basic()->set_nickname( nick );
}

bool Add::has_nickname() const
{
    return m_data->basic().has_nickname();
}

void Add::clear_nickname()
{
    m_data->mutable_basic()->clear_nickname();
}

String *Add::email()
{
    return m_data->mutable_basic()->mutable_email();
}

const String &Add::get_email() const
{
    return m_data->basic().email();
}

void Add::set_email(String email)
{
    m_data->mutable_basic()->set_email( email );
}

bool Add::has_email() const
{
    return m_data->basic().has_email();
}

void Add::clear_email()
{
    m_data->mutable_basic()->clear_email();
}

String *Add::password()
{
    return m_data->mutable_password();
}

const String &Add::get_password() const
{
    return m_data->password();
}

void Add::set_password(String pass)
{
    m_data->set_password( pass );
}

bool Add::has_password() const
{
    return m_data->has_password();
}

void Add::clear_password()
{
    m_data->clear_password();
}

String *Add::description()
{
    return m_data->mutable_basic()->mutable_description();
}

const String &Add::get_description() const
{
    return m_data->basic().description();
}

void Add::set_description(String desc)
{
    m_data->mutable_basic()->set_description( desc );
}

bool Add::has_description() const
{
    return m_data->basic().has_description();
}

void Add::clear_description()
{
    m_data->mutable_basic()->clear_description();
}

Bytes *Add::avatar()
{
    return m_data->mutable_basic()->mutable_avatar();
}

const Bytes &Add::get_avatar() const
{
    return m_data->basic().avatar();
}

void Add::set_avatar(Bytes avatar)
{
    m_data->mutable_basic()->set_avatar(move(avatar));
}

bool Add::has_avatar() const
{
    return m_data->basic().has_avatar();
}

void Add::clear_avatar()
{
    m_data->mutable_basic()->clear_avatar();
}

IAcl *Add::acl()
{
    if( !m_adp )
        m_adp = new ProtobufAclAdapter(m_data->mutable_acl());
    else
        m_adp->operator=(ProtobufAclAdapter(m_data->mutable_acl()));
    return m_adp;
}

const IAcl &Add::get_acl() const
{
    m_adp->operator=( ProtobufAclAdapter(const_cast<protobuf::Acl*>(&m_data->acl())));
    return *m_adp;
}

void Add::assign_acl( IAcl *acl)
{
    m_data->set_allocated_acl( dynamic_cast<ProtobufAclAdapter*>(acl)->detachData() );
    delete acl;
}

bool Add::has_acl() const
{
    return m_data->has_acl();
}

void Add::clear_acl()
{
    m_data->clear_acl();
}

String *Add::address()
{
    return m_data->mutable_details()->mutable_address();
}

const String &Add::get_address() const
{
    return m_data->details().address();
}

void Add::set_address(String ads)
{
    m_data->mutable_details()->set_address(std::move(ads));
}

bool Add::has_address() const
{
    return m_data->details().has_address();
}

void Add::clear_address()
{
    m_data->mutable_details()->clear_address();
}

String *Add::phoneNumber()
{
    return m_data->mutable_details()->mutable_phone_number();
}

const String &Add::get_phoneNumber() const
{
    return m_data->details().phone_number();
}

void Add::set_phoneNumber(String number)
{
    m_data->mutable_details()->set_phone_number(std::move(number));
}

bool Add::has_phoneNumber() const
{
    return m_data->details().has_phone_number();
}

void Add::clear_phoneNumber()
{
    m_data->mutable_details()->clear_phone_number();
}

protobuf::UserReq_Add *Add::detachData()
{
    take_ovnership = false;
    return m_data;
}

Login::Login():
    m_data(new protobuf::UserReq_Login() ), m_takeOvnership(true), m_auth(nullptr)
{
}

Login::Login(protobuf::UserReq_Login *login_msg):
    m_data(login_msg), m_auth(nullptr){
}

Login::~Login()
{
    if(m_takeOvnership){
        delete m_data;
    }
    if(m_auth)
        delete m_auth;
}

IAuthorizationData* Login::credentials()
{
    if(!m_auth)
        m_auth = new ProtobufAuthorizationDataAdapter( m_data->mutable_cred() );
    else
        m_auth->operator=(ProtobufAuthorizationDataAdapter( m_data->mutable_cred() ));
    return m_auth;
}

const IAuthorizationData &Login::get_credentials() const
{
    if(!m_auth)
        m_auth = new ProtobufAuthorizationDataAdapter( );
    m_auth->operator=(ProtobufAuthorizationDataAdapter( const_cast<protobuf::Credentials*>(&m_data->cred())));
    return *m_auth;
}

void Login::assign_credentials(IAuthorizationData* cred)
{
    m_data->set_allocated_cred( dynamic_cast<ProtobufAuthorizationDataAdapter*>(cred)->detachData() );
    delete cred;
}

bool Login::has_credentials() const
{
    return m_data->has_cred();
}

String *Login::password()
{
    return m_data->mutable_password();
}

const String &Login::get_password() const
{
    return m_data->password();
}

void Login::set_password(String pass)
{
    m_data->set_password(move(pass));
}

bool Login::has_password() const
{
    return m_data->has_password();
}

protobuf::UserReq_Login *Login::detachData()
{
    m_takeOvnership = false;
    return m_data;
}

Get::Get():
    m_data( new protobuf::UserReq_Get(protobuf::UserReq_Get::default_instance() ) ),
    m_takeOvnership(true),
    m_crit(nullptr)
{

}

Get::Get(protobuf::UserReq_Get *get):
    m_data( get ),
    m_takeOvnership(false),
    m_crit(nullptr)
{

}

Get::~Get()
{
    if(m_takeOvnership)
        delete m_data;
    if(m_crit)
        delete m_crit;
}

bool Get::has_requestedUid() const
{
    return m_data->has_uid() && m_data->uid();
}

void Get::request_uid(bool request)
{
    if(request)
        m_data->set_uid(true);
    else
        m_data->clear_uid();
}

bool Get::has_requestedAddress() const
{
    return m_data->has_address() && m_data->address();
}

void Get::request_address(bool request)
{
    if(request)
        m_data->set_address(true);
    else
        m_data->clear_address();
}

bool Get::has_requestedPhoneNumber() const
{
    return m_data->has_phone_number() && m_data->phone_number();
}

void Get::request_phoneNumber(bool request)
{
    if(request)
        m_data->set_phone_number(true);
    else
        m_data->clear_phone_number();
}

bool Get::has_requestedDescription() const
{
    return m_data->has_description() && m_data->description();
}

void Get::request_description(bool request)
{
    if(request)
        m_data->set_description(true);
    else
        m_data->clear_description();
}

bool Get::has_requestedAvatar() const
{
    return m_data->has_avatar() && m_data->avatar();
}

void Get::request_avatar(bool request)
{
    if(request)
        m_data->set_avatar(true);
    else
        m_data->clear_avatar();
}

bool Get::has_requestedAcl() const
{
    return m_data->has_acl() && m_data->acl();
}

void Get::request_acl(bool request)
{
    if(request)
        m_data->set_acl(true);
    else
        m_data->clear_acl();
}

requests::user::ICriterion *Get::criteria()
{
    if(!m_crit)
        m_crit = new user::Criterion(m_data->mutable_where());
    else
        m_crit->operator =(user::Criterion(m_data->mutable_where()));
    return m_crit;
}

void Get::assign(ICriterion *crit)
{
    m_data->set_allocated_where(dynamic_cast<user::Criterion*>(crit)->detachData() );
    delete crit;
}

const ICriterion &Get::get_criteria() const
{
    if(!m_crit)
        m_crit = new user::Criterion( );
    m_crit->operator =(user::Criterion(const_cast<protobuf::UserReq_Get_Where*>(&m_data->where())));
    return *m_crit;
}

protobuf::UserReq_Get *Get::detachData()
{
    m_takeOvnership = false;
    return m_data;
}
}
requests::user::IAdd* User::add()
{
    if( !m_add )
        m_add = new user::Add(m_data->mutable_add());
    else
        m_add->operator=(user::Add(m_data->mutable_add()));
    return m_add;
}

const user::IAdd &User::get_add() const
{
    if( !m_add )
        m_add = new user::Add();
    m_add->operator=( user::Add(const_cast<protobuf::UserReq_Add*>(&m_data->add())));
    return *m_add;
}

User::User():
    m_data(new protobuf::UserReq), m_takeOvnership(true), m_add(nullptr), m_login(nullptr), m_get(nullptr)
{
}

User::User(protobuf::UserReq *req):
    m_data(req), m_takeOvnership(false), m_add(nullptr), m_login(nullptr), m_get(nullptr)
{
}

User::~User()
{
    if(m_takeOvnership){
        delete m_data;
    }
    if(m_add)
        delete m_add;
    if(m_get)
        delete m_get;
    if(m_login)
        delete m_login;
}

bool User::has_add() const
{
    return m_data->has_add();
}

void User::clear_add()
{
    m_data->clear_add();
}

requests::user::ILogin* User::login()
{
    if( !m_login )
        m_login = new user::Login(m_data->mutable_login());
    else
        m_login->operator=(user::Login(m_data->mutable_login()));
    return m_login;
}

const user::ILogin &User::get_login() const
{
    if( !m_login )
        m_login = new user::Login();
    else
        m_login->operator=(user::Login( const_cast<protobuf::UserReq_Login*>(&m_data->login())));
    return *m_login;
}

void User::assign(requests::user::IAdd* add)
{
    m_data->set_allocated_add( dynamic_cast<user::Add*>(add)->detachData() );
    delete add;
}

void User::assign(requests::user::ILogin* login)
{
    m_data->set_allocated_login( dynamic_cast<user::Login*>(login)->detachData() );
    delete login;
}

void User::assign(requests::user::IGet* get)
{
    m_data->set_allocated_get( dynamic_cast<user::Get*>(get)->detachData() );
    delete get;
}

bool User::has_login() const
{
    return m_data->has_login();
}

void User::clear_login()
{
    m_data->clear_login();
}

requests::user::IGet* User::get()
{
    if( !m_get )
        m_get = new user::Get(m_data->mutable_get());
    m_get->operator=(user::Get(m_data->mutable_get()));
    return m_get;
}

const user::IGet &User::get_get() const
{
    if( !m_get )
        m_get = new user::Get();
    m_get->operator=( user::Get(const_cast<protobuf::UserReq_Get*>(&m_data->get())));
    return *m_get;
}

bool User::has_get() const
{
    return m_data->has_get();
}

void User::clear_get()
{
    m_data->clear_get();
}

protobuf::UserReq *User::detachData()
{
    m_takeOvnership = false;
    return m_data;
}

}


requests::user::Criterion::Criterion():
    Criterion(new protobuf::UserReq_Get_Where(protobuf::UserReq_Get_Where::default_instance()), true)
{

}

requests::user::Criterion::Criterion(protobuf::UserReq_Get_Where *msg):
    Criterion(msg,false)
{

}

requests::user::Criterion::~Criterion()
{
    if(m_takeOwnership)
        delete m_data;
}

void requests::user::Criterion::require_data_own(bool self)
{
    m_data->set_self(true);
}

void requests::user::Criterion::require_data_of_user(const IAuthorizationData &id)
{
    if(id.is_authorized_by_email())
        m_data->mutable_cred()->set_email(id.get_email());
    else if(id.is_authorized_by_id())
        m_data->mutable_cred()->set_id(id.get_uid());
    else
        m_data->mutable_cred()->set_nickname(id.get_nickname());
}

requests::user::Criterion::Criterion(protobuf::UserReq_Get_Where *msg, bool take):
    m_data(msg), m_takeOwnership(take)
{
}

bool requests::user::Criterion::has_requested_own_data() const
{
    return m_data->has_self() && m_data->self();
}

bool requests::user::Criterion::has_requested_foreign_uid() const
{
    return m_data->has_cred() && m_data->cred().has_id();
}

UID requests::user::Criterion::get_foreign_uid() const
{
    return m_data->cred().id();
}

protobuf::UserReq_Get_Where *requests::user::Criterion::detachData()
{
    m_takeOwnership = false;
    return m_data;
}
