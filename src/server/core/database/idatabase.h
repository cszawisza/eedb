#pragma once

#include <stack>
#include <mutex>
#include <thread>

#include "DbConnection.hpp"

using namespace std;

class DB;

///
/// \brief The DbConnectionStack class
/// contains database connections, avalible for every thread in application
/// when there is no more connections on stack new connection is created
///
class DbConnectionStack
{
private:
    friend class DB;

    static unique_ptr<DbConnection> pop();
    static void push(unique_ptr<DbConnection> &&db);
    static size_t size();

    static mutex m_dbMutex;
    static stack<unique_ptr<DbConnection>> m_databases;
};

class DB
{
    bool hasReservedConnection();

    //! function used when you want to take a conection from cnnection pool
    unique_ptr<DbConnection> takeFromPool();

    //! function pushech connection on stack
    void pushToPool();

    //! makes a connection "private" in connection stack
    void reserveTransaction( unique_ptr<DbConnection> &&con);

    //! pointer to database connection
    thread_local static unique_ptr<DbConnection> m_reserved;
public:
    using type = sqlpp::postgresql::connection;

    DB();
    ~DB();

    //! returns a bad connection handler (it only gives a type od connection)
    static DbConnection &connection();

    //! start transaction
    void start_transaction();

    //! create a savepoint
    void savepoint(const string &name);

    //! rollback to saving point
    void rollback_to(const string &name);

    //! commit transaction (or throw transaction if transaction has finished already)
    void commit_transaction();

    //! rollback transaction
    void rollback_transaction(bool report);

    //! report rollback failure
    void report_rollback_failure(const std::string &message) noexcept;

    //! execute an query
    size_t execute(const std::string &str, bool singleShoot = 0 );

    //! get last inserted id
    uint64_t lastInsertId( const std::string & tablename, const std::string & column);

    //! prepare
    template<typename T>
    auto prepare(const T& t) -> decltype(DbConnectionStack::pop()->prepare(t) ){
        auto deleter = [&]( DbConnection *db ){
            reserveTransaction( move(unique_ptr<DbConnection>(db)) );
        };

        unique_ptr<DbConnection, decltype(deleter)> db ( takeFromPool().release(), deleter );
        return db->prepare(t);
    }

    //! execute statement
    template<typename T>
    auto operator()(const T& t) -> decltype(DbConnectionStack::pop()->operator()(t) ) {
        auto deleter = [&]( DbConnection *db ){
            reserveTransaction( move(unique_ptr<DbConnection>(db)) );
        };

        unique_ptr<DbConnection, decltype(deleter)> db ( takeFromPool().release(), deleter );
        return db->operator()(t);
    }
};

//class Transaction : public DB {

//};
