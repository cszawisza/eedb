#pragma once

#include <QElapsedTimer>
#include <QDebug>

#include <sqlpp11/sqlpp11.h>
#include <sqlpp11/postgresql/postgresql.h>

#include <stack>
#include <memory>
#include <mutex>

using namespace std;

class DatabaseConnectionProvider;

class PerformanceCounter
{
public:
    PerformanceCounter(){
        timer.restart();
    }
    ~PerformanceCounter(){
        qDebug() << "query takes:" << timer.nsecsElapsed()/1000.0 << " µs";
    }

private:
    QElapsedTimer timer;
};

class DatabaseConnection : public sqlpp::postgresql::connection
{
public:
    DatabaseConnection();
private:
    static shared_ptr<sqlpp::postgresql::connection_config> getConf();
};

class DatabasePool
{
private:
    friend class DatabaseConnectionProvider;

    static unique_ptr<DatabaseConnection> getDatabase();
    static void returnDatabase(unique_ptr<DatabaseConnection> &&db);

    static mutex m_dbMutex;
    static stack<unique_ptr<DatabaseConnection>> m_databases;
};

class DatabaseConnectionProvider
{
    DatabasePool *m_parent;
    unique_ptr<DatabaseConnection> m_db;

public:
    DatabaseConnectionProvider( const DatabasePool *parent ):
        m_parent( const_cast<DatabasePool *>( parent ) ),
        m_db(m_parent->getDatabase()) {}
    ~DatabaseConnectionProvider(){
        m_parent->returnDatabase(move(m_db));
    }

//    const sqlpp::postgresql::connection &connection() const {
//        auto db = m_db.get();
//        return &dynamic_cast<sqlpp::postgresql::connection*> (db);
//    }

    template<typename T>
    auto operator()(const T& t) -> decltype(m_db->operator()(t) ) {
        PerformanceCounter perf;
        return m_db->operator()(t);
    }
};
