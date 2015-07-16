#pragma once

#include <string>

#include "database/UserHelper.hpp"

using std::string;

namespace test{
using eedb::db::UserHelper;

inline quint64 addUser(DB &db, const string &name){
    pb::MsgUserRequest_Add msg;

    msg.mutable_basic()->set_name(name);
    msg.mutable_basic()->set_email(name + "@fake.xx");
    msg.set_password("xxxx");

    if(! UserHelper::getUserIdByName(db, name)) // function returns 0 when user don't exist
        UserHelper::insertUser(db, msg);
    return UserHelper::getUserIdByName(db, name);
}

template<typename T>
inline void createBackup(DB &db, T ){
    string table =  sqlpp::name_of<T>::char_ptr();

    string copy = table +"_copy";

    db.execute("CREATE TABLE " + copy +" (LIKE "+ table + " INCLUDING ALL);");
    db.execute("ALTER TABLE " + copy + " ALTER c_uid DROP DEFAULT;");
    db.execute("CREATE SEQUENCE " + copy + "_id_seq;");

    db.execute("INSERT INTO " + copy + " SELECT * FROM "+ table + ";");
    db.execute("SELECT setval('" + copy + "_id_seq', (SELECT max(c_uid) FROM " + copy + "), true);");
    db.execute("ALTER TABLE " + copy + " ALTER c_uid SET DEFAULT nextval('" + copy + "_id_seq');");
}

template<typename T>
inline void createBackup( T t ){
    DB db;
    try{
        db.start_transaction();
        createBackup(db,t);
        db.commit_transaction();
    }
    catch(sqlpp::exception){
        db.rollback_transaction(false);
    }
}


template<typename T>
inline void restoreBackup(DB &db, T ){

    string table =  sqlpp::name_of<T>::char_ptr();
    string copy = table+ "_copy";
    db.execute("delete from "+ table + " where c_uid not in ( select c_uid from "+ copy + " );");

    db.execute("DROP table " + copy + ";");
    db.execute("DROP SEQUENCE " + copy + "_id_seq;");
}


template<typename T>
inline void restoreBackup( T t){
    DB db;
    try{
        db.start_transaction();
        restoreBackup(db, t);
        db.commit_transaction();
    }
    catch(sqlpp::exception){
        db.rollback_transaction(false);
    }
}


inline std::string random_string( size_t length )
{
    auto randchar = []() -> char
    {
        const char charset[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[ rand() % max_index ];
    };
    std::string str(length,0);
    std::generate_n( str.begin(), length, randchar );
    return str;
}
}
