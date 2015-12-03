#include "UserAdapter.hpp"
#include "AclAdapter.hpp"

#include "../../Interfaces/AclData.hpp"

using namespace data;

ProtobufUserAddAdapter::ProtobufUserAddAdapter():
    pb::UserReq_Add( pb::UserReq_Add::default_instance() ) {
}

UID ProtobufUserAddAdapter::get_id() const
{
    return basic().id();
}

void ProtobufUserAddAdapter::set_id(UID id)
{
    mutable_basic()->set_id( id );
}

bool ProtobufUserAddAdapter::has_id() const
{
    return basic().has_id();
}

void ProtobufUserAddAdapter::clear_id()
{
    mutable_basic()->clear_id();
}

String *ProtobufUserAddAdapter::nickname()
{
    return mutable_basic()->mutable_nickname();
}

const String &ProtobufUserAddAdapter::get_nickname() const
{
    return basic().nickname();
}

void ProtobufUserAddAdapter::set_nickname(String nick)
{
    mutable_basic()->set_nickname( nick );
}

bool ProtobufUserAddAdapter::has_nickname() const
{
    return basic().has_nickname();
}

void ProtobufUserAddAdapter::clear_nickname()
{
    mutable_basic()->clear_nickname();
}

String *ProtobufUserAddAdapter::email()
{
    return mutable_basic()->mutable_email();
}

const String &ProtobufUserAddAdapter::get_email() const
{
    return basic().email();
}

void ProtobufUserAddAdapter::set_email(String email)
{
    mutable_basic()->set_email( email );
}

bool ProtobufUserAddAdapter::has_email() const
{
    return basic().has_email();
}

void ProtobufUserAddAdapter::clear_email()
{
    mutable_basic()->clear_email();
}

String *ProtobufUserAddAdapter::password()
{
    return mutable_password();
}

const String &ProtobufUserAddAdapter::get_password() const
{
    return pb::UserReq_Add::password();
}

void ProtobufUserAddAdapter::set_password(String pass)
{
    pb::UserReq_Add::set_password( pass );
}

bool ProtobufUserAddAdapter::has_password() const
{
    return pb::UserReq_Add::has_password();
}

void ProtobufUserAddAdapter::clear_password()
{
    pb::UserReq_Add::clear_password();
}

String *ProtobufUserAddAdapter::description()
{
    return mutable_basic()->mutable_description();
}

const String &ProtobufUserAddAdapter::get_description() const
{
    return basic().description();
}

void ProtobufUserAddAdapter::set_description(String desc)
{
    mutable_basic()->set_description( desc );
}

bool ProtobufUserAddAdapter::has_description() const
{
    return basic().has_description();
}

void ProtobufUserAddAdapter::clear_description()
{
    mutable_basic()->clear_description();
}

Bytes *ProtobufUserAddAdapter::avatar()
{
    return mutable_basic()->mutable_avatar();
}

const Bytes &ProtobufUserAddAdapter::get_avatar() const
{
    return basic().avatar();
}

void ProtobufUserAddAdapter::set_avatar(Bytes avatar)
{
    mutable_basic()->set_avatar(move(avatar));
}

bool ProtobufUserAddAdapter::has_avatar() const
{
    return basic().has_avatar();
}

void ProtobufUserAddAdapter::clear_avatar()
{
    mutable_basic()->clear_avatar();
}

IAcl *ProtobufUserAddAdapter::acl()
{
    if( !has_acl() )
        this->set_allocated_acl(new ProtobufAclAdapter);
    return static_cast<IAcl*>(static_cast<ProtobufAclAdapter*>(mutable_acl()));
}

void ProtobufUserAddAdapter::assign_acl(IAcl *acl)
{
    this->set_allocated_acl( static_cast<ProtobufAclAdapter*>(acl) );
}

bool ProtobufUserAddAdapter::has_acl() const
{
    return pb::UserReq_Add::has_acl();
}

void ProtobufUserAddAdapter::clear_acl()
{
    pb::UserReq_Add::clear_acl();
}

String *ProtobufUserAddAdapter::address()
{
    return mutable_details()->mutable_address();
}

const String &ProtobufUserAddAdapter::get_address() const
{
    return details().address();
}

void ProtobufUserAddAdapter::set_address(String ads)
{
    mutable_details()->set_address(std::move(ads));
}

bool ProtobufUserAddAdapter::has_address() const
{
    return details().has_address();
}

void ProtobufUserAddAdapter::clear_address()
{
    mutable_details()->clear_address();
}

String *ProtobufUserAddAdapter::phoneNumber()
{
    return mutable_details()->mutable_address();
}

const String &ProtobufUserAddAdapter::get_phoneNumber() const
{
    return details().phone_number();
}

void ProtobufUserAddAdapter::set_phoneNumber(String number)
{
    mutable_details()->set_phone_number(std::move(number));
}

bool ProtobufUserAddAdapter::has_phoneNumber() const
{
    return details().has_phone_number();
}

void ProtobufUserAddAdapter::clear_phoneNumber()
{
    mutable_details()->mutable_phone_number();
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
    return mutable_password();
}

const String &ProtobufUserLoginAdapter::get_password() const
{
    return pb::UserReq_Login::password();
}

void ProtobufUserLoginAdapter::set_password(String pass)
{
    pb::UserReq_Login::set_password(move(pass));
}

bool ProtobufUserLoginAdapter::has_password() const
{
    return pb::UserReq_Login::has_password();
}


requests::user::IAdd *ProtobufUserAdapter::add()
{
    if( !has_add() )
        this->set_allocated_add(new ProtobufUserAddAdapter);
    return static_cast<requests::user::IAdd*>(static_cast<ProtobufUserAddAdapter*>(mutable_add()));
}

void ProtobufUserAdapter::assign(requests::user::IAdd *add)
{
    this->set_allocated_add( static_cast<ProtobufUserAddAdapter*>(add) );
}

bool ProtobufUserAdapter::has_add() const
{
    return pb::UserReq::has_add();
}

void ProtobufUserAdapter::clear_add()
{
    pb::UserReq::clear_add();
}

requests::user::ILogin *ProtobufUserAdapter::login()
{
    if( !has_add() )
        this->set_allocated_login(new ProtobufUserLoginAdapter);
    return static_cast<requests::user::ILogin*>(static_cast<ProtobufUserLoginAdapter*>(mutable_login()));
}

void ProtobufUserAdapter::assign(requests::user::ILogin *login)
{
    this->set_allocated_login( static_cast<ProtobufUserLoginAdapter*>(login) );
}

bool ProtobufUserAdapter::has_login() const
{
    return pb::UserReq::has_login();
}

void ProtobufUserAdapter::clear_login()
{
    pb::UserReq::clear_login();
}
