#pragma once

#include "string"

struct UnixPerms {
    UnixPerms(std::initializer_list<unsigned int> perms );
    UnixPerms( const char *perms );
    UnixPerms() = default;
    unsigned int other : 3;
    unsigned int group : 3;
    unsigned int owner : 3;
} __attribute((__packed__));

class UnixPermissions{
public:
    UnixPermissions( UnixPerms perms );
    UnixPermissions( int perms );

    int toInteger() const;
    std::string toString() const;
private:
    UnixPerms m_perms;
};
