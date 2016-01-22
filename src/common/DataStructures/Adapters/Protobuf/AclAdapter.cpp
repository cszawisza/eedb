#include "AclAdapter.hpp"

#include "common.pb.h"

UID ProtobufAclAdapter::get_id() const
{
    return m_data->uid();
}

void ProtobufAclAdapter::set_id(UID uid)
{
    m_data->set_uid(uid);
}

bool ProtobufAclAdapter::has_id() const
{
    return m_data->has_uid();
}

void ProtobufAclAdapter::clear_id()
{
    m_data->clear_uid();
}

UID ProtobufAclAdapter::get_owner() const
{
    return m_data->owner();
}

void ProtobufAclAdapter::set_owner(UID uid)
{
    m_data->set_owner( uid );
}

bool ProtobufAclAdapter::has_owner() const
{
    return m_data->has_owner();
}

void ProtobufAclAdapter::clear_owner()
{
    m_data->clear_owner();
}

UID ProtobufAclAdapter::get_groups() const
{
    return m_data->group();
}

void ProtobufAclAdapter::set_groups(UID uid)
{
    m_data->set_group( uid );
}

bool ProtobufAclAdapter::has_groups() const
{
    return m_data->has_group();
}

void ProtobufAclAdapter::clear_groups()
{
    m_data->clear_group();
}

UnixPermissions ProtobufAclAdapter::get_unixperms() const
{
    ///FIXME
}

void ProtobufAclAdapter::set_unixperms(UnixPermissions)
{
}

bool ProtobufAclAdapter::has_unixperms() const
{
    return m_data->has_unixperms();
}

void ProtobufAclAdapter::clear_unixperms()
{
    m_data->clear_unixperms();
}

Status ProtobufAclAdapter::get_status() const
{
    return static_cast<Status>(m_data->status());
}

void ProtobufAclAdapter::set_status(Status status)
{
    m_data->set_status(static_cast<uint32_t>(status));
}

bool ProtobufAclAdapter::has_status() const
{
    return m_data->has_status();
}

void ProtobufAclAdapter::clear_status()
{
    m_data->clear_status();
}

protobuf::Acl *ProtobufAclAdapter::detachData(){
    take_ovnership = false;
    return m_data;
}

ProtobufAclAdapter::ProtobufAclAdapter():
    m_data(new protobuf::Acl ), take_ovnership(true){}


ProtobufAclAdapter::ProtobufAclAdapter(protobuf::Acl *p):
    m_data(p), take_ovnership(false)
{
}

ProtobufAclAdapter::~ProtobufAclAdapter()
{
    if(take_ovnership)
        delete m_data;
}
