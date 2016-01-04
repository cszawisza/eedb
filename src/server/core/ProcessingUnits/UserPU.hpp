#pragma once

#include "iprocessor.h"

class DB;

namespace requests{
namespace user{
class IAdd;
class ILogin;
class ILogout;
}
}


namespace eedb {
namespace pu {

class UserPU : public IMessageProcessingUnit
{
public:
    UserPU() {}
    virtual ~UserPU() {}

    // MessageHandler interface
public:
    void process( IClientRequest *msgReq ) override;
    void process( DB &db, IClientRequest *msgReq ) override;

private:
    void handle_add         (DB &db, const requests::user::IAdd &msg    );
    void handle_login       (DB &db, const requests::user::ILogin &loginMsg  );
//    void handle_logout      (DB &db, const protobuf::UserReq_Logout &logoutMsg );
//    void handle_modify      (DB &db, const protobuf::UserReq_Modify &msg );
//    void handle_remove      (DB &db, const protobuf::UserReq_Remove &delateMsg );
//    void handle_get         (DB &db, const protobuf::UserReq_Get    &getMsg    );
//    void handle_changePasswd(DB &db, const protobuf::UserReq_ChangePasswd &msg );


    void addUser(DB &db, const requests::user::IAdd &msg );
    void goToOnlineState(DB &db, uint64_t uid);
    bool userExists(DB &db, const string &name, const string &email );

    void raise_addErrorCode(int err);
    void raise_loginError(int err);

    void loadUserCache(DB &db, uint64_t uid);
//    void addResponseMessage();
};

}
}
