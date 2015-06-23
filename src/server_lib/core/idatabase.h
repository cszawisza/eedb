#pragma once

#include <QElapsedTimer>
#include <QDebug>

#include <sqlpp11/sqlpp11.h>
#include <sqlpp11/postgresql/postgresql.h>

#include <stack>
#include <memory>
#include <mutex>
#include <unordered_map>
#include <thread>

using namespace std;

class DB;

class PerformanceCounter
{
public:
    PerformanceCounter(QString msg="");
    ~PerformanceCounter();

private:
    QElapsedTimer timer;
    QString m_additional;
};

class DbConnection : public sqlpp::postgresql::connection
{
public:
    DbConnection( std::shared_ptr<sqlpp::postgresql::connection_config> conf = getConf() );
    static void SetGlobalDbName( std::string name );
private:

    static shared_ptr<sqlpp::postgresql::connection_config> getConf();
};

///
/// \brief The DbConnectionStack class
/// contains database connections, avalible for every thread in application
/// when there is no more connections on stack new connection is created
///
class DbConnectionStack
{
public:

private:
    friend class DB;

    static unique_ptr<DbConnection> getDatabase();
    static void returnDatabase(unique_ptr<DbConnection> &&db);
    static size_t getDbNumber();

    static void reserveDatabase(unique_ptr<DbConnection> &&db);
    static unique_ptr<DbConnection> getReservedDb();
    static bool hasReserved();

    static void killall();

    static mutex m_dbMutex;
    static mutex m_dbReserve;
    static stack<unique_ptr<DbConnection>> m_databases;
    static map<thread::id, unique_ptr<DbConnection>> m_reserved;
};

// To make this class muvable, don't hold pointer to database in it!
class DB
{
    bool hasReservedConnection() {
        return DbConnectionStack::hasReserved();
    }
    //! function used when you want to take a conection from cnnection pool
    unique_ptr<DbConnection> takeFromPool(){
        if(hasReservedConnection())
            return DbConnectionStack::getReservedDb();
        return DbConnectionStack::getDatabase();
    }
    //! function pushech connection on stack
    void pushToPool(){
        if(hasReservedConnection())
            DbConnectionStack::returnDatabase(move(DbConnectionStack::getReservedDb()));
    }

    //! makes a connection "private" in connection stack
    void reserveTransaction( unique_ptr<DbConnection> &&con) {
        DbConnectionStack::reserveDatabase(move(con));
    }

public:

    DB();
    ~DB();

    //! returns a bad connection handler (it only gives a type od connection)
    DbConnection &connection(){
        unique_ptr<DbConnection> con;
        return *con.get();
    }

    //! start transaction
    void start_transaction() {
        auto db = takeFromPool();
        db->start_transaction();
        reserveTransaction( move(db) );
    }

    //! commit transaction (or throw transaction if transaction has finished already)
    void commit_transaction() {
        /// Throw error when no reserved are available
        /// or create a new connection and wait for "not started" transaction then?
        auto db = takeFromPool();
        try{
            db->commit_transaction();
        }
        catch (sqlpp::exception e){
            reserveTransaction(move(db));
            throw e;
        }
        reserveTransaction( move(db));
    }

    //! rollback transaction
    void rollback_transaction(bool report) {
        /// Throw error when no reserved are available
        /// or create a new connection and wait for "not started" transaction then?
        auto db = takeFromPool();
        try{
            db->rollback_transaction(report);
        }
        catch (sqlpp::exception e){
            reserveTransaction(move(db));
            throw e;
        }
        reserveTransaction(move(db));
    }

    //! report rollback failure
    void report_rollback_failure(const std::string &message) noexcept;

    size_t execute(const std::string &str, bool singleShoot = false){
        auto db = takeFromPool();
        auto size = db->execute(str);
        if(!singleShoot)
            reserveTransaction(move(db));
        return size;
    }

    template<typename T>
    auto prepare(const T& t) -> decltype(DbConnectionStack::getDatabase()->prepare(t) ){
        auto db = takeFromPool();
        auto res = db->prepare(t);
        reserveTransaction( move(db));
        return res;
    }

    template<typename T>
    auto operator()(const T& t) -> decltype(DbConnectionStack::getDatabase()->operator()(t) ) {
        auto db = takeFromPool();
        auto res = db->operator()(t);
        reserveTransaction(move(db));
        return res;
    }

    quint64 lastInsertId( const std::string & tablename, const std::string & column) {
        auto db = takeFromPool();
        auto res = db->last_insert_id(tablename, column);
        reserveTransaction(move(db));
        return res;
    }
};
