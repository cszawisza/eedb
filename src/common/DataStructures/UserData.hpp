#pragma once

#include "StructuresCommon.hpp"

namespace data{
namespace requests{
namespace user{

struct Credentials{
    boost::variant<boost::blank, Name, Email, UID> data;
};

class Add : public WireData{
public:
    boost::optional<Email> email;
    boost::optional<Name> name;
    boost::optional<String> password;
    boost::optional<UID> id;
    boost::optional<String> description;
    boost::optional<String> address;
    boost::optional<String> phoneNumber;
    OptBytes avatarData;
    OptAcl acl;
};

class Login: public WireData{
public:
    Credentials cred;
    OptString password;
};

class Logout: public WireData{

};

class Modify: public WireData{

};

class Get: public WireData{

};
}

class User: public WireData{
public:

private:
    boost::variant<
    user::Add,
    user::Login,
    user::Logout,
    user::Credentials
    > data;
};
}
}
