#pragma once

#include "../../Interfaces/AclData.hpp"
#include "common.pb.h"

namespace data{
    class Acl;
}

class ProtobufAclAdapter : public data::IAcl, public pb::Acl {
public:
    ProtobufAclAdapter();

    data::UID get_id() const;
    void set_id(data::UID uid);
    bool has_id() const;
    void clear_id();

    data::UID get_owner() const;
    void set_owner(data::UID uid);
    bool has_owner() const;
    void clear_owner();

    data::UID get_groups() const;
    void set_groups(data::UID uid);
    bool has_groups() const;
    void clear_groups();

    UnixPermissions get_unixperms() const;
    void set_unixperms(UnixPermissions);
    bool has_unixperms() const;
    void clear_unixperms();

    data::Status get_status() const;
    void set_status(data::Status status);
    bool has_status() const;
    void clear_status();
};
