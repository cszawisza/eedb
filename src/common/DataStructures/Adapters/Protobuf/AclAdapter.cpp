#include "AclAdapter.hpp"

data::UID ProtobufAclAdapter::get_id() const
{
    return uid();
}

void ProtobufAclAdapter::set_id(data::UID uid)
{
    set_uid(uid);
}

bool ProtobufAclAdapter::has_id() const
{
    return has_uid();
}

void ProtobufAclAdapter::clear_id()
{
    clear_uid();
}

data::UID ProtobufAclAdapter::get_owner() const
{
    return pb::Acl::owner();
}

void ProtobufAclAdapter::set_owner(data::UID uid)
{
    pb::Acl::set_owner( uid );
}

bool ProtobufAclAdapter::has_owner() const
{
    return pb::Acl::has_owner();
}

void ProtobufAclAdapter::clear_owner()
{
    pb::Acl::clear_owner();
}

data::UID ProtobufAclAdapter::get_groups() const
{
    return group();
}

void ProtobufAclAdapter::set_groups(data::UID uid)
{
    set_group( uid );
}

bool ProtobufAclAdapter::has_groups() const
{
    return has_group();
}

void ProtobufAclAdapter::clear_groups()
{
    clear_group();
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
    return pb::Acl::has_unixperms();
}

void ProtobufAclAdapter::clear_unixperms()
{
    pb::Acl::clear_unixperms();
}

data::Status ProtobufAclAdapter::get_status() const
{
    return static_cast<data::Status>(status());
}

void ProtobufAclAdapter::set_status(data::Status status)
{
    pb::Acl::set_status(static_cast<uint32_t>(status));
}

bool ProtobufAclAdapter::has_status() const
{
    return pb::Acl::has_status();
}

void ProtobufAclAdapter::clear_status()
{
    pb::Acl::clear_status();
}

ProtobufAclAdapter::ProtobufAclAdapter():
    pb::Acl( pb::Acl::default_instance() ){}
