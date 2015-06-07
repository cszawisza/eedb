#include "idatabase.h"

std::mutex DatabasePool::m_dbMutex;
stack<unique_ptr<DatabaseConnection>> DatabasePool::m_databases;

unique_ptr<DatabaseConnection> DatabasePool::getDatabase(){
    m_dbMutex.lock();
    if( m_databases.empty() ){
        m_dbMutex.unlock(); // create database is quite expensive, unlock before that
        return unique_ptr<DatabaseConnection>( new DatabaseConnection() );
    }
    auto moved = move(m_databases.top());
    m_databases.pop();
    m_dbMutex.unlock();
    return move(moved);
}

void DatabasePool::returnDatabase(unique_ptr<DatabaseConnection> &&db) {
    lock_guard<mutex>lock(m_dbMutex);
    m_databases.push( move(db) );
}

DatabaseConnection::DatabaseConnection():
    sqlpp::postgresql::connection( getConf() ){}

shared_ptr<sqlpp::postgresql::connection_config> DatabaseConnection::getConf()
{
    auto conf = std::shared_ptr<sqlpp::postgresql::connection_config>( new sqlpp::postgresql::connection_config );
    conf->host = "localhost";
    conf->dbname = "postgres";
    conf->user = "postgres";
    conf->password = "postgres";
    conf->debug = true;
    return std::move(conf);
}

PerformanceCounter::PerformanceCounter(QString msg):
    m_additional(msg)
{
    timer.restart();
}

PerformanceCounter::~PerformanceCounter(){
    qDebug() << m_additional << " query takes:" << timer.nsecsElapsed()/1000.0 << " µs";
}


DatabaseConnectionProvider::DatabaseConnectionProvider(const DatabasePool *parent):
    m_parent( const_cast<DatabasePool *>( parent ) ),
    m_db(m_parent->getDatabase()) {}

DatabaseConnectionProvider::~DatabaseConnectionProvider(){
    ///TODO check if a transaction is started
    m_parent->returnDatabase(move(m_db));
}
