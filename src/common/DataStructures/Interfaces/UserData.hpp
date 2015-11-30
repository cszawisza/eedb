#pragma once

#include "../StructuresCommon.hpp"

namespace data{

class IAcl;

namespace requests{
namespace user{

class IAdd{
public:
    virtual UID get_id() const = 0;
    virtual void set_id( UID ) =0;
    virtual bool has_id() const = 0;
    virtual void clear_id() = 0;

    virtual String* nickname() = 0;
    virtual const String& get_nickname() const = 0;
    virtual void set_nickname( String ) = 0;
    virtual bool has_nickname() const = 0;
    virtual void clear_nickname() = 0;

    virtual String* email() = 0;
    virtual const String& get_email() const = 0;
    virtual void set_email( String ) = 0;
    virtual bool has_email() const = 0;
    virtual void clear_email() = 0;

    virtual String* password() = 0;
    virtual const String& get_password() const = 0;
    virtual void set_password( String ) = 0;
    virtual bool has_password() const = 0;
    virtual void clear_password() = 0;

    virtual String* description() = 0;
    virtual const String& get_description() const = 0;
    virtual void set_description( String ) = 0;
    virtual bool has_description() const = 0;
    virtual void clear_description() = 0;

    virtual Bytes* avatar() = 0;
    virtual const Bytes& get_avatar() const = 0;
    virtual void set_avatar( Bytes ) =0;
    virtual bool has_avatar() const = 0;
    virtual void clear_avatar() = 0;

    virtual IAcl* acl() =0;
    virtual void assign_acl( IAcl* ) = 0;
    virtual bool has_acl() const = 0;
    virtual void clear_acl() = 0;

    virtual String* address() = 0;
    virtual const String& get_address() const = 0;
    virtual void set_address( String ) = 0;
    virtual bool has_address() const = 0;
    virtual void clear_address() = 0;

    virtual String* phoneNumber() = 0;
    virtual const String& get_phoneNumber() const = 0;
    virtual void set_phoneNumber( String number ) = 0;
    virtual bool has_phoneNumber() const = 0;
    virtual void clear_phoneNumber() = 0;
};

class ILogin{
public:
    virtual Credentials* credentials() = 0;
    virtual const Credentials& get_credentials() const = 0;
    virtual void set_credentials( Credentials ) = 0;
    virtual bool has_credentials() const = 0;

    virtual String* password() = 0;
    virtual const String& get_password() const = 0;
    virtual void set_password( String ) =0;
    virtual bool has_password() const = 0;
};

class ILogout{
};

class IModify{
    /** set new value of email field */
    virtual bool modify_email() const =0;
    /** new value of email (NULL or not) */
    virtual boost::optional<Email> get_email() = 0;
    /** sets modify_email to true and email to Email or NULL */
    virtual void set_new_email( boost::optional<Email> ) = 0;
};

class IGet{
public:
    struct Criterion{
        void self( bool );
        void userId( UID );
    };
public:
    virtual bool has_requestedUid() const = 0;
    virtual void request_uid( bool ) = 0;

    virtual bool has_requestedAddress() const = 0;
    virtual void request_address( bool ) = 0;

    virtual bool has_requestedPhoneNumber() const = 0;
    virtual void request_phoneNumber( bool ) = 0;

    virtual bool has_requestedDescription() const = 0;
    virtual void request_description( bool ) = 0;

    virtual bool has_requestedAvatar() const = 0;
    virtual void request_avatar( bool ) = 0;

    virtual bool has_requestedAcl() const = 0;
    virtual void request_acl( bool ) = 0;

    virtual void set_requestCriterion( Criterion ) = 0;
    virtual const Criterion get_criteria() const = 0;
};

}

}
}
