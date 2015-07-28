#pragma once

#include "iprocessor.h"
#include "user.pb.h"

class DB;

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
    void process(DB &db, pb::ClientRequest &msgReq );

private:
    void handle_add   (DB &db, MsgUserRequest_Add    &msg    );
    void handle_login (DB &db, const MsgUserRequest_Login  &loginMsg  );
    void handle_logout(DB &db, const MsgUserRequest_Logout &logoutMsg );
    void handle_modify(DB &db, const MsgUserRequest_Modify &msg );
    void handle_remove(DB &db, const MsgUserRequest_Remove &delateMsg );
    void handle_get   (DB &db, const MsgUserRequest_Get    &getMsg    );
    void handle_changePasswd (DB &db, const MsgUserRequest_ChangePasswd &msg );


    void addUser(DB &db, const MsgUserRequest_Add &msg);
    void goToOnlineState(DB &db, quint64 uid);
    bool userExists(DB &db, string name, string email );
    void addErrorCode(MsgUserResponse_Reply err);
    void loadUserCache(DB &db, quint64 uid);
    void addResponseMessage();

    pb::MsgUserResponse m_response;
};

}
}
