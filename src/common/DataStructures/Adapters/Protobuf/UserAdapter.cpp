#include "UserAdapter.hpp"
#include "AclAdapter.hpp"
#include "user.pb.h"

#include "CommonDataStructuresAdapter.hpp"
#include "UserAdapter.hpp"

#include "../../Interfaces/AclData.hpp"
#include "../../Interfaces/UserRequests.hpp"

using namespace data;

namespace requests {
namespace user{

ProtobufUserAddAdapter::ProtobufUserAddAdapter():
    m_data(new pb::UserReq_Add()), take_ovnership(true), m_adp( new ProtobufAclAdapter() )
{
}

ProtobufUserAddAdapter::ProtobufUserAddAdapter(pb::UserReq_Add *msg):
    m_data(msg), m_adp( new ProtobufAclAdapter() )
{
}

ProtobufUserAddAdapter::~ProtobufUserAddAdapter()
{
    if(take_ovnership){
        delete m_data;
        if(m_adp)
            delete m_adp;
    }
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
    m_data->mutable_basic()->set_avatar(move(avatar));
}

bool ProtobufUserAddAdapter::has_avatar() const
{
    return m_data->basic().has_avatar();
}

void ProtobufUserAddAdapter::clear_avatar()
{
    m_data->mutable_basic()->clear_avatar();
}

IAcl *ProtobufUserAddAdapter::acl()
{
    if( !m_adp )
        m_adp = new ProtobufAclAdapter(m_data->mutable_acl());
    else
        m_adp->operator=(ProtobufAclAdapter(m_data->mutable_acl()));
    return m_adp;
}

const IAcl &ProtobufUserAddAdapter::get_acl() const
{
    m_adp->operator=( ProtobufAclAdapter(const_cast<pb::Acl*>(&m_data->acl())));
    return *m_adp;
}

void ProtobufUserAddAdapter::assign_acl( IAcl *acl)
{
    m_data->set_allocated_acl( dynamic_cast<ProtobufAclAdapter*>(acl)->detachData() );
    delete acl;
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
    return m_data->mutable_details()->mutable_phone_number();
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
    m_data->mutable_details()->clear_phone_number();
}

pb::UserReq_Add *ProtobufUserAddAdapter::detachData()
{
    take_ovnership = false;
    return m_data;
}

ProtobufUserLoginAdapter::ProtobufUserLoginAdapter():
    m_data(new pb::UserReq_Login() ), m_takeOvnership(true), m_auth(nullptr)
{
}

ProtobufUserLoginAdapter::ProtobufUserLoginAdapter(pb::UserReq_Login *login_msg):
    m_data(login_msg), m_auth(nullptr){
}

ProtobufUserLoginAdapter::~ProtobufUserLoginAdapter()
{
    if(m_takeOvnership){
        delete m_data;
        if(m_auth)
            delete m_auth;
    }
}

IAuthorizationData* ProtobufUserLoginAdapter::credentials()
{
    if(!m_auth)
        m_auth = new ProtobufAuthorizationDataAdapter( m_data->mutable_cred() );
    else
        m_auth->operator=(ProtobufAuthorizationDataAdapter( m_data->mutable_cred() ));
    return m_auth;
}

void ProtobufUserLoginAdapter::assign_credentials(IAuthorizationData* cred)
{
    m_data->set_allocated_cred( dynamic_cast<ProtobufAuthorizationDataAdapter*>(cred)->detachData() );
    delete cred;
}

bool ProtobufUserLoginAdapter::has_credentials() const
{
    return m_data->has_cred();
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

ProtobufUserGetAdapter::ProtobufUserGetAdapter():
    m_data( new pb::UserReq_Get(pb::UserReq_Get::default_instance() ) ),
    m_takeOvnership(true)
{

}

ProtobufUserGetAdapter::ProtobufUserGetAdapter(pb::UserReq_Get *get):
    m_data( get ),
    m_takeOvnership(false)
{

}

ProtobufUserGetAdapter::~ProtobufUserGetAdapter()
{
    if(m_takeOvnership)
        delete m_data;
}

bool ProtobufUserGetAdapter::has_requestedUid() const
{
    return m_data->has_uid() && m_data->uid();
}

void ProtobufUserGetAdapter::request_uid(bool request)
{
    if(request)
        m_data->set_uid(true);
    else
        m_data->clear_uid();
}

bool ProtobufUserGetAdapter::has_requestedAddress() const
{
    return m_data->has_address() && m_data->address();
}

void ProtobufUserGetAdapter::request_address(bool request)
{
    if(request)
        m_data->set_address(true);
    else
        m_data->clear_address();
}

bool ProtobufUserGetAdapter::has_requestedPhoneNumber() const
{
    return m_data->has_phone_number() && m_data->phone_number();
}

void ProtobufUserGetAdapter::request_phoneNumber(bool request)
{
    if(request)
        m_data->set_phone_number(true);
    else
        m_data->clear_phone_number();
}

bool ProtobufUserGetAdapter::has_requestedDescription() const
{
    return m_data->has_description() && m_data->description();
}

void ProtobufUserGetAdapter::request_description(bool request)
{
    if(request)
        m_data->set_description(true);
    else
        m_data->clear_description();
}

bool ProtobufUserGetAdapter::has_requestedAvatar() const
{
    return m_data->has_avatar() && m_data->avatar();
}

void ProtobufUserGetAdapter::request_avatar(bool request)
{
    if(request)
        m_data->set_avatar(true);
    else
        m_data->clear_avatar();
}

bool ProtobufUserGetAdapter::has_requestedAcl() const
{
    return m_data->has_acl() && m_data->acl();
}

void ProtobufUserGetAdapter::request_acl(bool request)
{
    if(request)
        m_data->set_acl(true);
    else
        m_data->clear_acl();
}

requests::user::ICriterion *ProtobufUserGetAdapter::criteria()
{

}

void ProtobufUserGetAdapter::set_requestCriterion(ICriterion *)
{
    ///FIXME
}

const ICriterion &ProtobufUserGetAdapter::getCriteria() const
{
    ///FIXME
}

pb::UserReq_Get *ProtobufUserGetAdapter::detachData()
{
    m_takeOvnership = false;
    return m_data;
}
}
requests::user::IAdd* ProtobufUserAdapter::add()
{
    if( !m_add )
        m_add = new user::ProtobufUserAddAdapter(m_data->mutable_add());
    else
        m_add->operator=(user::ProtobufUserAddAdapter(m_data->mutable_add()));
    return m_add;
}

ProtobufUserAdapter::ProtobufUserAdapter():
    m_data(new pb::UserReq), m_takeOvnership(true), m_add(nullptr), m_login(nullptr), m_get(nullptr)
{
}

ProtobufUserAdapter::ProtobufUserAdapter(pb::UserReq *req):
    m_data(req), m_add(nullptr), m_login(nullptr), m_get(nullptr)
{
}

ProtobufUserAdapter::~ProtobufUserAdapter()
{
    if(m_takeOvnership){
        delete m_data;

        if(m_add)
            delete m_add;
        if(m_get)
            delete m_get;
        if(m_login)
            delete m_login;
    }
}

bool ProtobufUserAdapter::has_add() const
{
    return m_data->has_add();
}

void ProtobufUserAdapter::clear_add()
{
    m_data->clear_add();
}

requests::user::ILogin* ProtobufUserAdapter::login()
{
    if( !m_login )
        m_login = new user::ProtobufUserLoginAdapter(m_data->mutable_login());
    else
        m_login->operator=(user::ProtobufUserLoginAdapter(m_data->mutable_login()));
    return m_login;
}

void ProtobufUserAdapter::assign(requests::user::IAdd* add)
{
    ///TODO check if dynamic cast failed, copy data if so
    m_data->set_allocated_add( dynamic_cast<user::ProtobufUserAddAdapter*>(add)->detachData() );
    delete add;
}

void ProtobufUserAdapter::assign(requests::user::ILogin* login)
{
    ///TODO check if dynamic cast failed, copy data if so
    m_data->set_allocated_login( dynamic_cast<user::ProtobufUserLoginAdapter*>(login)->detachData() );
    delete login;
}

void ProtobufUserAdapter::assign(requests::user::IGet* get)
{
    ///TODO check if dynamic cast failed, copy data if so
    m_data->set_allocated_get( dynamic_cast<user::ProtobufUserGetAdapter*>(get)->detachData() );
    delete get;
}

bool ProtobufUserAdapter::has_login() const
{
    return m_data->has_login();
}

void ProtobufUserAdapter::clear_login()
{
    m_data->clear_login();
}

requests::user::IGet* ProtobufUserAdapter::get()
{
    if( !m_get )
        m_get = new user::ProtobufUserGetAdapter(m_data->mutable_get());
    else
        m_get->operator=(user::ProtobufUserGetAdapter(m_data->mutable_get()));
    return m_get;
}

bool ProtobufUserAdapter::has_get() const
{
    return m_data->has_get();
}

void ProtobufUserAdapter::clear_get()
{
    m_data->clear_get();
}

pb::UserReq *ProtobufUserAdapter::detachData()
{
    m_takeOvnership = false;
    return m_data;
}

}
