#include "gtest/gtest.h"

#include <sqlpp11/sqlpp11.h>
#include "core/user.h"
#include <core/idatabase.h>
#include <memory>

/// TODO PK
void createBackup( string table, string copy){
    DB db;
    db.execute("CREATE TABLE " + copy +" (LIKE "+ table + " INCLUDING ALL);");
    db.execute("ALTER TABLE " + copy + " ALTER c_uid DROP DEFAULT;");
    db.execute("CREATE SEQUENCE " + copy + "_id_seq;");

    db.execute("INSERT INTO " + copy + " SELECT * FROM "+ table + ";");
    db.execute("SELECT setval('" + copy + "_id_seq', (SELECT max(c_uid) FROM " + copy + "), true);");
    db.execute("ALTER TABLE " + copy + " ALTER c_uid SET DEFAULT nextval('" + copy + "_id_seq');");
}

void restoreBackup( string table, string copy ){
    DB db;
    db.execute("delete from "+ table + " where c_uid not in ( select c_uid from "+ copy + " );");

    db.execute("DROP table " + copy + ";");
    db.execute("DROP SEQUENCE " + copy + "_id_seq;");
}

class userCreateTest : public ::testing::Test
{
public:
    userCreateTest() {
        createBackup("t_users", "t_users_copy");
    }

    ~userCreateTest(){
        restoreBackup("t_users", "t_users_copy");
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


TEST_F( userCreateTest, user_no_password_or_email){
    user::MsgUserRequest_Add req;

    req.set_password("passwd");
    auto res = sendRequest(req);
    EXPECT_TRUE(res.error());

    req.mutable_details()->set_name("Test_user_asdf");
    res = sendRequest(req);
    EXPECT_TRUE(res.error());

    req.mutable_details()->set_email("TestUser@user.uu");
    res = sendRequest(req);
    EXPECT_FALSE(res.error());
}

TEST_F( userCreateTest, user_name_to_long ){
    user::MsgUserRequest_Add req;

    req.set_password("passwd");
    auto res = sendRequest(req);
    EXPECT_TRUE(res.error());
}
