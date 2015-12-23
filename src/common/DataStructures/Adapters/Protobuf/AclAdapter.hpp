#pragma once

#include "../../Interfaces/AclData.hpp"

namespace pb{
    class Acl;
}

namespace data{
    class Acl;
}

class ProtobufAclAdapter : public IAcl {
public:
    ProtobufAclAdapter();
    ProtobufAclAdapter( pb::Acl *p);
    ~ProtobufAclAdapter();

    UID get_id() const;
    void set_id(UID uid);
    bool has_id() const;
    void clear_id();

    UID get_owner() const;
    void set_owner(UID uid);
    bool has_owner() const;
    void clear_owner();

    UID get_groups() const;
    void set_groups(UID uid);
    bool has_groups() const;
    void clear_groups();

    UnixPermissions get_unixperms() const;
    void set_unixperms(UnixPermissions);
    bool has_unixperms() const;
    void clear_unixperms();

    Status get_status() const;
    void set_status(Status status);
    bool has_status() const;
    void clear_status();

    pb::Acl *detachData();
private:
    pb::Acl *m_data;
    bool take_ovnership = false;
};
