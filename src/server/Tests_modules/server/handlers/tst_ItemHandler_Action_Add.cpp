#include "gtest/gtest.h"
#include "TestCommon.hpp"

#include "DataStructures/Adapters/Protobuf/ClientRequestAdapter.hpp"
#include "DataStructures/Adapters/Protobuf/ServerResponseAdapter.hpp"

using namespace eedb::db;
using namespace test;

constexpr schema::items i;
constexpr schema::users u;

//class ItemHandlerAddTest : public ::testing::Test
//{
//public:

//    ItemHandlerAddTest(){
//        db.start_transaction();

//        test::addUser(db, "xxxxxxx");
//        sut.setUserData(test::login(db, "xxxxxxx")); // go online
//        rootCategoryId = eedb::db::CategoryHelper::rootCategoryId(db).get_value_or(0);
//    }

//    ~ItemHandlerAddTest(){
//        db.rollback_transaction(false);
//    }

////    void insertTestGroups(){
////        constexpr schema::categories c;
////        auto rootCat = db(select(c.uid).from(c).where(c.parent_category_id.is_null())).front().uid;
////        auto cat1id = db(sqlpp::postgresql::insert_into(c).set(c.name = "cat_1_1", c.parent_category_id = rootCat).returning(c.uid)).front().uid;
////        db(sqlpp::postgresql::insert_into(c).set(c.name = "cat_2_1", c.parent_category_id = cat1id));
////        db(sqlpp::postgresql::insert_into(c).set(c.name = "cat_2_2", c.parent_category_id = cat1id));
////    }

//    ServerResponse runMessageHandlerProcess(){
//        ClientRequest cliReq;
//        auto catReq = cliReq.mutable_itemreq();
//        catReq->mutable_add()->MergeFrom(addMsg);

//        sut.process( db, cliReq );

//        return sut.getLastResponse();
//    }

//    void upgradeUserPrivileges(){
//        db(update(u).set(u.stat_group = sqlpp::verbatim<sqlpp::integer>( std::string(tableName<decltype(u)>()) + ".stat_group | (1<<4)" )).where(u.name == "xxxxxxx" )); ///FIXME
//    }

//protected:
//    DB db;
//    ItemReq_Add addMsg;
//    eedb::pu::ItemPU sut;
//    quint64 rootCategoryId;
//    void prepareMessage();
//};
//void ItemHandlerAddTest::prepareMessage()
//{
//    addMsg.set_name("new item name");
//    addMsg.set_symbol("SYMBOL1234567890");
//    addMsg.set_description("My description");
//    addMsg.set_is_private(true);
//    addMsg.set_category_id(rootCategoryId);
//}

//TEST_F(ItemHandlerAddTest, normalUserCanAddOnlyPrivateItems ){
//    prepareMessage();
    
//    addMsg.set_is_private(false);
//    auto res = runMessageHandlerProcess();
//    EXPECT_EQ(res.code(), Error_AccesDeny );
//    res.Clear();
    
//    addMsg.set_is_private(true);
//    res = runMessageHandlerProcess();
//    EXPECT_NE(res.has_code(), Error_AccesDeny );
//}

//TEST_F(ItemHandlerAddTest, addItemSavesItInDatabase ){
//    prepareMessage();

//    auto res = runMessageHandlerProcess();

//    const auto &sel = select(all_of(i)).from(i).where(i.name == "new item name");

//    EXPECT_TRUE( res.has_itemres() );
//    ASSERT_TRUE( db(select(exists(sel))).front().exists );

//    const auto &row = db(sel).front();
//    EXPECT_EQ( sut.user()->id(), row.owner );
//    EXPECT_EQ( "new item name", string(row.name) );
//    EXPECT_EQ( "SYMBOL1234567890", string(row.symbol));
//    EXPECT_EQ( "My description", string(row.description));
//}


//TEST_F(ItemHandlerAddTest, returnsId){
//    prepareMessage();
//    addMsg.set_returning_id(true);
//    auto res = runMessageHandlerProcess();
//    EXPECT_GT( res.itemres().id(), 0 );
//}

//TEST_F(ItemHandlerAddTest, addUnexistingParameterShouldFail ){
//    prepareMessage();

//    auto parameter = addMsg.add_parameters();
//    parameter->set_id(0);
//    addMsg.set_returning_id(true);
    
//    auto res = runMessageHandlerProcess();
//    EXPECT_EQ( res.itemres().code(), ItemResponse_Replay_ParameterDontExists );
//}


