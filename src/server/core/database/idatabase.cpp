#include "idatabase.h"
#include <QThread>
#include <thread>


std::mutex DbConnectionStack::m_dbMutex;

stack<unique_ptr<DbConnection>> DbConnectionStack::m_databases;
thread_local unique_ptr<DbConnection> DB::m_reserved;


unique_ptr<DbConnection> DbConnectionStack::pop(){
    ///TODO check config to check is connection uses default settings or not
    m_dbMutex.lock();
    if( m_databases.empty() )
        m_databases.push(unique_ptr<DbConnection>( new DbConnection() ));

    auto moved = move(m_databases.top());
    m_databases.pop();
    m_dbMutex.unlock();
    return move(moved);
}

void DbConnectionStack::push(unique_ptr<DbConnection> &&db) {
    lock_guard<mutex>lock(m_dbMutex);
    m_databases.push( move(db) );
}

size_t DbConnectionStack::size(){
    lock_guard<mutex>lock(m_dbMutex);
    return m_databases.size();
}



bool DB::hasReservedConnection() {
    return m_reserved != nullptr;
}

unique_ptr<DbConnection> DB::takeFromPool(){
    if(hasReservedConnection())
        return move(m_reserved);
    return DbConnectionStack::pop();
}

void DB::pushToPool(){
    if(hasReservedConnection())
        DbConnectionStack::push(move(m_reserved));
}

void DB::reserveTransaction(unique_ptr<DbConnection> &&con) {
    m_reserved = move(con);
}

DB::DB(){}

DB::~DB(){
    pushToPool();
}

DbConnection &DB::connection(){
    unique_ptr<DbConnection> con;
    return *con.get();
}

void DB::start_transaction() {
    auto deleter = [&]( DbConnection *db ){
        reserveTransaction( move(unique_ptr<DbConnection>(db)) );
    };

    unique_ptr<DbConnection, decltype(deleter)> db ( takeFromPool().release(), deleter );
    db->start_transaction();
}

void DB::savepoint(const string &name){
    auto deleter = [&]( DbConnection *db ){
        reserveTransaction( move(unique_ptr<DbConnection>(db)) );
    };

    unique_ptr<DbConnection, decltype(deleter)> db ( takeFromPool().release(), deleter );
    db->savepoint(name);
}

void DB::rollback_to(const string &name){
    auto deleter = [&]( DbConnection *db ){
        reserveTransaction( move(unique_ptr<DbConnection>(db)) );
    };

    unique_ptr<DbConnection, decltype(deleter)> db ( takeFromPool().release(), deleter );
    db->rollback_to_savepoint(name);
}

void DB::commit_transaction() {
    auto deleter = [&]( DbConnection *db ){
        reserveTransaction( move(unique_ptr<DbConnection>(db)) );
    };

    unique_ptr<DbConnection, decltype(deleter)> db ( takeFromPool().release(), deleter );
    db->commit_transaction();
}

void DB::rollback_transaction(bool report) {
    auto deleter = [&]( DbConnection *db ){
        reserveTransaction( move(unique_ptr<DbConnection>(db)) );
    };

    unique_ptr<DbConnection, decltype(deleter)> db ( takeFromPool().release(), deleter );
    db->rollback_transaction(report);
}

size_t DB::execute(const string &str, bool singleShoot){
    auto db = takeFromPool();
    auto res = db->execute(str);
    if(!singleShoot)
        reserveTransaction(move(db));
    return 0 ; ///FIXME res->result->affected_rows();
}

uint64_t DB::lastInsertId(const string &tablename, const string &column) {
    auto deleter = [&]( DbConnection *db ){
        reserveTransaction( move(unique_ptr<DbConnection>(db)) );
    };

    unique_ptr<DbConnection, decltype(deleter)> db ( takeFromPool().release(), deleter );
    return db->last_insert_id(tablename, column);
}
