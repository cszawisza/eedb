#include "gtest/gtest.h"

#include <sqlpp11/sqlpp11.h>
#include "core/user.h"
#include <core/idatabase.h>
#include <memory>

#include "../../common.h"

class userLoginTest : public ::testing::Test
{
public:
   userLoginTest() {
       createBackup("t_users");
       createBackup("t_login_history");
   }

   ~userLoginTest(){
       restoreBackup("t_users");
       restoreBackup("t_login_history");
   }

   const ResponseCode &sendRequest( user::MsgUserRequest_Add &msg){
       protbuf::ClientRequest req;

       auto userReq = req.mutable_msguserreq();
       userReq->mutable_add()->CopyFrom(msg);

       handler.process(req);

       return handler.getLastResponse().codes(0);
   }

   eedb::handlers::User handler;
};

