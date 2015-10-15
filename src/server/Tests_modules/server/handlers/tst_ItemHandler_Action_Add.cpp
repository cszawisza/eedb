#include "gtest/gtest.h"

#include <core/database/idatabase.h>
#include <core/ItemPU.hpp>
#include <core/database/ItemHelper.hpp>

#include "TestCommon.hpp"

using namespace eedb::db;
using namespace test;

constexpr schema::items i;
constexpr schema::users u;

class ItemHandlerAddTest : public ::testing::Test
{
public:

    ItemHandlerAddTest(){
        db.start_transaction();

        auth::Privilege priv;
        priv.giveGroup(auth::GROUP_users).privilegeFor("add_private_item").forTable(i).force_save(db);

        test::addUser(db, "xxxxxxx");
        sut.setUserData(test::login(db, "xxxxxxx")); // go online
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
        ClientRequest cliReq;
        auto catReq = cliReq.mutable_itemreq();
        catReq->mutable_add()->MergeFrom(addMsg);

        sut.process( db, cliReq );

        return sut.getLastResponse();
    }

    void upgradeUserPrivileges(){
        auth::Privilege priv;
        priv.giveGroup(auth::GROUP_items).privilegeFor("add_public_item").forTable(i).force_save(db);
        db(update(u).set(u.stat_group = sqlpp::verbatim<sqlpp::integer>( std::string(tableName<decltype(u)>()) + ".stat_group | (1<<4)" )).where(u.name == "xxxxxxx" )); ///FIXME
    }

protected:
    DB db;
    ItemRequest_Add addMsg;
    eedb::pu::ItemPU sut;
};

TEST_F(ItemHandlerAddTest, normalUserCanAddOnlyPrivateItems ){
    addMsg.set_name("new item name");
    addMsg.set_symbol("SYMBOL1234567890");
    addMsg.set_description("My description");
    addMsg.set_is_private(false);

    auto res = runMessageHandlerProcess();
    EXPECT_EQ(res.code(), Error_AccesDeny );
    res.Clear();

    addMsg.set_is_private(true);
    res = runMessageHandlerProcess();
    EXPECT_NE(res.code(), Error_AccesDeny );
}

