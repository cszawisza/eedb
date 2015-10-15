#pragma once

#include "iprocessor.h"
#include "user.pb.h"

class DB;

namespace eedb {
namespace pu {

using namespace pb;

class User : public IMessageProcessingUint
{
public:
    User() {}
    virtual ~User() {}

    // MessageHandler interface
public:
    void process(pb::ClientRequest &msgReq );
    void process(DB &db, pb::ClientRequest &msgReq );

private:
    void handle_add   (DB &db, UserReq_Add    &msg    );
    void handle_login (DB &db, const UserReq_Login  &loginMsg  );
    void handle_logout(DB &db, const UserReq_Logout &logoutMsg );
    void handle_modify(DB &db, const UserReq_Modify &msg );
    void handle_remove(DB &db, const UserReq_Remove &delateMsg );
    void handle_get   (DB &db, const UserReq_Get    &getMsg    );
    void handle_changePasswd (DB &db, const UserReq_ChangePasswd &msg );


    void addUser(DB &db, const UserReq_Add &msg);
    void goToOnlineState(DB &db, uint64_t uid);
    bool userExists(DB &db, string name, string email );
    void addErrorCode(UserRes_Reply err);
    void loadUserCache(DB &db, uint64_t uid);
    void addResponseMessage();

    pb::UserRes m_response;
};

}
}
