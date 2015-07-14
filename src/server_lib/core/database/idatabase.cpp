#include "idatabase.h"
#include <QThread>
#include <thread>


std::mutex DbConnectionStack::m_dbMutex;
std::mutex DbConnectionStack::m_dbReserve;

stack<unique_ptr<DbConnection>> DbConnectionStack::m_databases;
map<thread::id, unique_ptr<DbConnection>> DbConnectionStack::m_reserved;
static string dbName = "postgres";

unique_ptr<DbConnection> DbConnectionStack::getDatabase(){
    ///TODO check config to check is connection uses default settings or not
    m_dbMutex.lock();
    if( m_databases.empty() )
        m_databases.push(unique_ptr<DbConnection>( new DbConnection() ));

    auto moved = move(m_databases.top());
    m_databases.pop();
    m_dbMutex.unlock();
    return move(moved);
}

void DbConnectionStack::returnDatabase(unique_ptr<DbConnection> &&db) {
    lock_guard<mutex>lock(m_dbMutex);
    m_databases.push( move(db) );
}

size_t DbConnectionStack::getDbNumber(){
    lock_guard<mutex>lock(m_dbMutex);
    return m_databases.size();
}

void DbConnectionStack::reserveDatabase(unique_ptr<DbConnection> &&db)
{
    lock_guard<mutex>lock(m_dbReserve);
    m_reserved.insert(pair<thread::id, unique_ptr<DbConnection> >(this_thread::get_id(), move(db)));
}

unique_ptr<DbConnection> DbConnectionStack::getReservedDb()
{
    lock_guard<mutex>lock(m_dbReserve);

    auto id = this_thread::get_id();
    auto moved = move(m_reserved[id]);
    m_reserved.erase(id);
    return move(moved);
}

bool DbConnectionStack::hasReserved()
{
    lock_guard<mutex>lock(m_dbReserve);
    return m_reserved.count( this_thread::get_id() ) > 0;
}


DbConnection::DbConnection(std::shared_ptr<sqlpp::postgresql::connection_config> conf):
    sqlpp::postgresql::connection( conf ){}

void DbConnection::SetGlobalDbName(string name){
    dbName = name;
}

shared_ptr<sqlpp::postgresql::connection_config> DbConnection::getConf()
{
    auto conf = std::shared_ptr<sqlpp::postgresql::connection_config>( new sqlpp::postgresql::connection_config );
    conf->host = "localhost";
    conf->dbname = dbName;
    conf->user = "postgres";
    conf->password = "postgres";
    //conf->debug = true;
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


DB::DB(){}

DB::~DB(){
    pushToPool();
}
