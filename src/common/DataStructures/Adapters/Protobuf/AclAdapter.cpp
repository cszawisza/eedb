#include "AclAdapter.hpp"

#include "common.pb.h"

data::UID ProtobufAclAdapter::get_id() const
{
    return m_data->uid();
}

void ProtobufAclAdapter::set_id(data::UID uid)
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

data::UID ProtobufAclAdapter::get_owner() const
{
    return m_data->owner();
}

void ProtobufAclAdapter::set_owner(data::UID uid)
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

data::UID ProtobufAclAdapter::get_groups() const
{
    return m_data->group();
}

void ProtobufAclAdapter::set_groups(data::UID uid)
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

data::Status ProtobufAclAdapter::get_status() const
{
    return static_cast<data::Status>(m_data->status());
}

void ProtobufAclAdapter::set_status(data::Status status)
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

pb::Acl *ProtobufAclAdapter::detachData(){
    take_ovnership = false;
    return m_data;
}

ProtobufAclAdapter::ProtobufAclAdapter():
    m_data(new pb::Acl ), take_ovnership(true){}


ProtobufAclAdapter::ProtobufAclAdapter(pb::Acl *p):
    m_data(p)
{
}

ProtobufAclAdapter::~ProtobufAclAdapter()
{
    if(take_ovnership)
        delete m_data;
}
