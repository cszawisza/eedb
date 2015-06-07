#pragma once

#include "iprocessor.h"
#include "idatabase.h"

#include "user.pb.h"

namespace core {
namespace parsers {

using namespace user;

class User : public MessageHandler, public DatabasePool
{
public:
    User() {}
    virtual ~User() {}

    // MessageHandler interface
public:
    void process();

private:
    void parse_add   (const MsgUserRequest_Add    &msg    );
    void parse_login ( const MsgUserRequest_Login  &loginMsg  );
    void parse_logout( const MsgUserRequest_Logout &logoutMsg );
    void parse_modify( const MsgUserRequest_Modify &modifyMsg );
    void parse_remove( const MsgUserRequest_Remove &delateMsg );
    void parse_get   ( const MsgUserRequest_Get    &getMsg    );
};

}
}
