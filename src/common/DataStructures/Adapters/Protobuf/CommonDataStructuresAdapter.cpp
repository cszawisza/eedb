#include "CommonDataStructuresAdapter.hpp"

#include "common.pb.h"

#include "../Validators/EmailValidator.hpp"
#include "../Validators/NickNameValidator.hpp"

#include <boost/lexical_cast.hpp>

ProtobufAuthorizationDataAdapter::ProtobufAuthorizationDataAdapter():
    m_data( new protobuf::Credentials( protobuf::Credentials::default_instance() ) ), m_takeOvnership(true)
{

}

ProtobufAuthorizationDataAdapter::ProtobufAuthorizationDataAdapter(protobuf::Credentials *cred):
    m_data( cred ), m_takeOvnership(false)
{

}

ProtobufAuthorizationDataAdapter::ProtobufAuthorizationDataAdapter(const protobuf::Credentials &cred):
    m_data( const_cast<protobuf::Credentials*>(&cred) ), m_takeOvnership(false)
{

}

ProtobufAuthorizationDataAdapter::~ProtobufAuthorizationDataAdapter()
{
    if(m_takeOvnership)
        delete m_data;
}

void ProtobufAuthorizationDataAdapter::set_authorization(boost::variant<String, UID> auth)
{
    m_data->Clear();

    if( auth.type() == typeid(String) ){
        const auto &auth_str = boost::get<String>(auth);
        EmailValidator emailValidator;
        NickNameValidator nicknameValidator;

        if(nicknameValidator.isValid(auth_str))
            m_data->set_nickname(auth_str);
        else if(emailValidator.isValid(auth_str))
            m_data->set_email(auth_str);
        else{
            try{
                auth = boost::lexical_cast<UID>(auth_str.data());
            }
            catch( boost::bad_lexical_cast e){
               auth = 0;
            }
        }
    }

    if(auth.type() == typeid(UID))
        m_data->set_id(boost::get<UID>(auth));

}

bool ProtobufAuthorizationDataAdapter::is_authorized_by_email() const
{
    return m_data->has_email();
}

bool ProtobufAuthorizationDataAdapter::is_authorized_by_nickname() const
{
    return m_data->has_nickname();
}

bool ProtobufAuthorizationDataAdapter::is_authorized_by_id() const
{
    return m_data->has_id();
}

const String &ProtobufAuthorizationDataAdapter::get_email() const
{
    return m_data->email();
}

const String &ProtobufAuthorizationDataAdapter::get_nickname() const
{
    return m_data->nickname();
}

UID ProtobufAuthorizationDataAdapter::get_uid() const
{
    return m_data->id();
}

void ProtobufAuthorizationDataAdapter::Clear() const
{
    m_data->Clear();
}

protobuf::Credentials *ProtobufAuthorizationDataAdapter::detachData()
{
    m_takeOvnership = false;
    return m_data;
}
