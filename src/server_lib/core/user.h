#pragma once

#include "iprocessor.h"
#include "idatabase.h"

#include "pb_cpp/user.pb.h"

namespace eedb {
namespace handlers {

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
    void handle_add   (const MsgUserRequest_Add    &msg    );
    void handle_login ( const MsgUserRequest_Login  &loginMsg  );
    void handle_logout( const MsgUserRequest_Logout &logoutMsg );
    void handle_modify( const MsgUserRequest_Modify &modifyMsg );
    void handle_remove( const MsgUserRequest_Remove &delateMsg );
    void handle_get   ( const MsgUserRequest_Get    &getMsg    );
};

}
}
