#pragma once

#include "iprocessor.h"
#include "idatabase.h"

#include "user.pb.h"

namespace eedb {
namespace handlers {

using namespace pb;

class User : public MessageHandler
{
public:
    User() {}
    virtual ~User() {}

    // MessageHandler interface
public:
    void process(pb::ClientRequest &msgReq );

private:
    void handle_add   (MsgUserRequest_Add    &msg    );
    void handle_login ( const MsgUserRequest_Login  &loginMsg  );
    void handle_logout( const MsgUserRequest_Logout &logoutMsg );
    void handle_modify(const MsgUserRequest_Modify &msg );
    void handle_remove( const MsgUserRequest_Remove &delateMsg );
    void handle_get   ( const MsgUserRequest_Get    &getMsg    );
    void handle_changePasswd (const MsgUserRequest_ChangePasswd &msg );


    void goToOnlineState(DB &db, quint64 uid);
    bool userExists(DB &db, string name, string email );
    void addUser(DB &db, const MsgUserRequest_Add &msg);
    void addResp(bool isError, Replay err_code);
    void loadUserCache(DB &db, quint64 uid);
};

}
}
