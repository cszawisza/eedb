#pragma once

#include <string>
#include "core/idatabase.h"

using std::string;

inline void createBackup( string table){
    DB db;
    string copy = table +"_copy";

    db.execute("CREATE TABLE " + copy +" (LIKE "+ table + " INCLUDING ALL);");
    db.execute("ALTER TABLE " + copy + " ALTER c_uid DROP DEFAULT;");
    db.execute("CREATE SEQUENCE " + copy + "_id_seq;");

    db.execute("INSERT INTO " + copy + " SELECT * FROM "+ table + ";");
    db.execute("SELECT setval('" + copy + "_id_seq', (SELECT max(c_uid) FROM " + copy + "), true);");
    db.execute("ALTER TABLE " + copy + " ALTER c_uid SET DEFAULT nextval('" + copy + "_id_seq');");
}

inline void restoreBackup( string table ){
    DB db;
    string copy = table+ "_copy";
    db.execute("delete from "+ table + " where c_uid not in ( select c_uid from "+ copy + " );");

    db.execute("DROP table " + copy + ";");
    db.execute("DROP SEQUENCE " + copy + "_id_seq;");
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
