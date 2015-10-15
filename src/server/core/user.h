#pragma once

#include "iprocessor.h"

class DB;

namespace pb {
    class ClientRequest;
    class UserReq_Add;
    class UserReq_Login;
    class UserReq_Modify;
    class UserReq_Remove;
    class UserReq_Get;
    class UserReq_ChangePasswd;
}

namespace eedb {
namespace pu {

class UserPU : public IMessageProcessingUint
{
public:
    UserPU() {}
    virtual ~UserPU() {}

    // MessageHandler interface
public:
    void process(pb::ClientRequest &msgReq );
    void process(DB &db, pb::ClientRequest &msgReq );

private:
    void handle_add         (DB &db,       pb::UserReq_Add    &msg    );
    void handle_login       (DB &db, const pb::UserReq_Login  &loginMsg  );
    void handle_logout      (DB &db, const pb::UserReq_Logout &logoutMsg );
    void handle_modify      (DB &db, const pb::UserReq_Modify &msg );
    void handle_remove      (DB &db, const pb::UserReq_Remove &delateMsg );
    void handle_get         (DB &db, const pb::UserReq_Get    &getMsg    );
    void handle_changePasswd(DB &db, const pb::UserReq_ChangePasswd &msg );


    void addUser(DB &db, const pb::UserReq_Add &msg);
    void goToOnlineState(DB &db, uint64_t uid);
    bool userExists(DB &db, string name, string email );
    void addErrorCode(pb::UserRes_Reply err);
    void loadUserCache(DB &db, uint64_t uid);
    void addResponseMessage();

    pb::UserRes m_response;
};

}
}
