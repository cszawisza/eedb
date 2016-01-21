#include "gtest/gtest.h"

#include "core/database/idatabase.h"
#include "sqlpp11/sqlpp11.h"

#include <sqlpp11/table.h>
#include <sqlpp11/char_sequence.h>
#include <sqlpp11/column_types.h>

using sqlpp::postgresql::pg_exception;

namespace t_test_ {

struct x {
    struct _alias_t {
        static constexpr const char _literal[] ="x";
        using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
        template<typename T>
        struct _member_t {
            T x;
            T &operator()() { return x; }
            const T &operator()() const { return x; }
        };
    };

    using _traits = sqlpp::make_traits<sqlpp::integer>;
};
}

struct t_test : sqlpp::table_t<t_test, t_test_::x> {
    using _value_type = sqlpp::no_value_t;
    struct _alias_t {
        static constexpr const char _literal[] = "t_test";
        using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
        template<typename T>
        struct _member_t {
            T t_test;
            T &operator()() { return t_test; }
            const T &operator()() const { return t_test; }
        };
    };
};

constexpr t_test test;

TEST(DB, connectToDatabaseAndSimpleQUery){
    DB db;
    EXPECT_NO_THROW(db.execute("select true;")); // database is connected
}

TEST(DB, transactionOwnsTheConnection ){
    DB db;

    // no started transactions yet should throw
    // really???
    //    EXPECT_THROW(db.commit_transaction()      , sqlpp::exception );
    //    EXPECT_THROW(db.rollback_transaction(true), sqlpp::exception );

    EXPECT_THROW(db.savepoint("save"), pg_exception ); // should throw, not in transaction
    EXPECT_THROW(db.rollback_to("save"), pg_exception );

    EXPECT_NO_THROW(db.commit_transaction()       );
    EXPECT_NO_THROW(db.rollback_transaction(true) );

    EXPECT_NO_THROW(db.start_transaction());
    EXPECT_NO_THROW(db.rollback_transaction(true));

    EXPECT_NO_THROW(db.start_transaction());
    EXPECT_NO_THROW(db.savepoint("save"));
    EXPECT_NO_THROW(db.rollback_to("save"));
    EXPECT_NO_THROW(db.commit_transaction());
}

TEST(DB, transaction){
    DB db;

    EXPECT_NO_THROW(db.start_transaction());
    EXPECT_NO_THROW(db.execute("create temporary table if not exists t_test (x int);"));
    EXPECT_NO_THROW(db(sqlpp::postgresql::insert_into(test).set(test.x = 5)));
    EXPECT_EQ( db(select(test.x).from(test).where(true)).front().x, 5);
    EXPECT_NO_THROW(db.rollback_transaction(false));
}

TEST(DB, prepare){
    DB db;
    EXPECT_NO_THROW(db.start_transaction());
    EXPECT_NO_THROW(db.execute("create temporary table if not exists t_test (x int);"));
    EXPECT_NO_THROW(db(sqlpp::postgresql::insert_into(test).set(test.x = 5)));
    auto q = dynamic_select(db.connection(), test.x )
            .from(test)
            .dynamic_where();
    EXPECT_EQ( db(q).front().x, 5);
    EXPECT_NO_THROW(db.rollback_transaction(false));
}

TEST(DB, multipleTransactionsInDifferentObjects){
    DB db;
    EXPECT_NO_THROW(db.start_transaction());
    {
        DB db2; // should be the same connection

        EXPECT_NO_THROW(db2.execute("create temporary table if not exists t_test (x int);"));
        EXPECT_NO_THROW(db2(sqlpp::postgresql::insert_into(test).set(test.x = 5)));
        auto q = dynamic_select(db2.connection(), test.x )
                .from(test)
                .dynamic_where();
        EXPECT_EQ( db2(q).front().x,5);
        EXPECT_NO_THROW(db2.rollback_transaction(false));
    }

    db.execute("select avg(i) from generate_series(12345,1234500) as i");
}

void test_thread(){
    DB db;
    // "big" query
    db.execute("select avg(i) from generate_series(12345,1234500) as i");
}

SQLPP_ALIAS_PROVIDER(i)

TEST(DB, eachThreadHaveOwnConnection){
    auto t1 = std::thread(test_thread);
    auto t2 = std::thread(test_thread);
    auto t3 = std::thread(test_thread);
    auto t4 = std::thread(test_thread);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
}

//SQLPP_ALIAS_PROVIDER(aaa)
//void test2_thread(){
//    for(int i=300;i>0; i--){
//        DB db;
//        auto r = rand();
//        auto ret = db(select( sqlpp::verbatim<sqlpp::integer>( std::to_string(r)).as(aaa) ).where(true)).front().aaa;
//        EXPECT_EQ(r, ret);
//    }
//}

//void test3_thread(){
//    for(int i=100;i>0; i--){
//        DB db;
//        EXPECT_NO_THROW(db.start_transaction());
//        EXPECT_NO_THROW(db.execute("create temporary table if not exists t_test (x int);"));
//        EXPECT_NO_THROW(db(sqlpp::postgresql::insert_into(test).set(test.x = 5)));
//        auto q = dynamic_select(db.connection(), test.x )
//                .from(test)
//                .dynamic_where();
//        EXPECT_EQ( db(q).front().x, 5);
//        EXPECT_NO_THROW(db.rollback_transaction(false));
//    }
//}

//TEST(DB, stressTest) // not really
//{
//    srand(0);
//    static const int t = 2;
//    std::thread threads[t*2];

//    for(int i=0;i<t;i++){
//        threads[i] = std::thread(test2_thread);
//    }
//    for(int i=t;i<t*2;i++){
//        threads[i] = std::thread(test3_thread);
//    }

//    for(int i=0;i<t*2;i++){
//        threads[i].join();
//    }
//}
