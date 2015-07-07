#include "gtest/gtest.h"

#include <sqlpp11/sqlpp11.h>
#include <core/idatabase.h>
#include <memory>

#include "../../common.h"

#include "sql_schema/t_user_inventories.h"
#include "core/storage.h"

class inventoryTest : public ::testing::Test
{
public:
    inventoryTest() {
        schema::t_users u;
        createBackup(u);
    }

    ~inventoryTest(){
        schema::t_users u;
        restoreBackup(u);
    }

    const ResponseCode &addUser( pb::MsgUserRequest_Add &msg){
//        protbuf::ClientRequest req;

//        auto userReq = req.mutable_msguserreq();
//        userReq->mutable_add()->CopyFrom(msg);

//        handler.process(req);

//        return handler.getLastResponse().codes(0);
    }
};
