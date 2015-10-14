#include "gtest/gtest.h"

#include <core/database/idatabase.h>
#include <core/ItemHandler.hpp>

#include "TestCommon.hpp"

using namespace eedb::db;
using namespace test;


class ItemHandlerAddTest : public ::testing::Test
{
public:

    ItemHandlerAddTest(){
        db.start_transaction();

//        test::addUser(db, "xxxxxxx");
//        handler.setUserData(test::login(db, "xxxxxxx")); // go online
    }

    ~ItemHandlerAddTest(){
        db.rollback_transaction(false);
    }

//    void insertTestGroups(){
//        constexpr schema::categories c;
//        auto rootCat = db(select(c.uid).from(c).where(c.parent_category_id.is_null())).front().uid;
//        auto cat1id = db(sqlpp::postgresql::insert_into(c).set(c.name = "cat_1_1", c.parent_category_id = rootCat).returning(c.uid)).front().uid;
//        db(sqlpp::postgresql::insert_into(c).set(c.name = "cat_2_1", c.parent_category_id = cat1id));
//        db(sqlpp::postgresql::insert_into(c).set(c.name = "cat_2_2", c.parent_category_id = cat1id));
//    }

    ServerResponse runMessageHandlerProcess(){
//        ClientRequest cliReq;
//        auto catReq = cliReq.mutable_categoryreq();
//        catReq->mutable_get()->MergeFrom(getMsg);

//        handler.process( db, cliReq );

//        return handler.getLastResponse();
    }

//    void upgradeUserPrivileges(){
//        auth::Privilege priv;
//        constexpr schema::categories c;
//        constexpr schema::users u;
//        priv.giveGroup(auth::GROUP_categories).privilegeFor("write").forTable(c).force_save(db);
//        db(update(u).set(u.stat_group = sqlpp::verbatim<sqlpp::integer>( std::string(tableName<decltype(u)>()) + ".stat_group | (1<<3)" )).where(u.name == "xxxxxxx" )); ///FIXME
//    }

protected:
    DB db;
    ItemRequest_Add addMsg;
//    eedb::handlers::Category handler;
};

