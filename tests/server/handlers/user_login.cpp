#include "gtest/gtest.h"

#include <sqlpp11/sqlpp11.h>
#include "core/user.h"
#include <core/idatabase.h>
#include <memory>

#include "../../common.h"

#include "sql_schema/t_users.h"
#include "sql_schema/t_user_history.h"

class userLoginTest : public ::testing::Test
{
public:
   userLoginTest() {
       schema::t_users u;
       schema::t_user_history uh;
       createBackup(u);
       createBackup(uh);
   }

   ~userLoginTest(){
       schema::t_users u;
       schema::t_user_history uh;

       restoreBackup(u);
       restoreBackup(uh);
   }

   const ResponseCode &sendRequest( pb::MsgUserRequest_Add &msg){
       protbuf::ClientRequest req;

       auto userReq = req.mutable_msguserreq();
       userReq->mutable_add()->CopyFrom(msg);

       handler.process(req);

       return handler.getLastResponse().codes(0);
   }

   eedb::handlers::User handler;
};

