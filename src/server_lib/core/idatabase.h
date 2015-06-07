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
    PerformanceCounter(QString msg="");
    ~PerformanceCounter();

private:
    QElapsedTimer timer;
    QString m_additional;
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
    DatabaseConnectionProvider( const DatabasePool *parent );
    ~DatabaseConnectionProvider();

    DatabaseConnection &connection(){
        return *m_db.get();
    }

    //! start transaction
    void start_transaction(){
        return m_db->start_transaction();
    }

    //! commit transaction (or throw transaction if transaction has
    // finished already)
    void commit_transaction(){
        return m_db->commit_transaction();
    }

    //! rollback transaction
    void rollback_transaction(bool report){
        return m_db->rollback_transaction(report);
    }

    //! report rollback failure
    void report_rollback_failure(const std::string &message) noexcept;

    template<typename T>
    auto prepare(const T& t) -> decltype(m_db->prepare(t) ){
        PerformanceCounter perf("Prepare");
        return m_db->prepare(t);
    }

    template<typename T>
    auto operator()(const T& t) -> decltype(m_db->operator()(t) ) {
        PerformanceCounter perf();
        return m_db->operator()(t);
    }
};
