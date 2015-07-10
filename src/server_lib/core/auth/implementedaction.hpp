#pragma once
#include <sqlpp11/sqlpp11.h>
#include "sql_schema/t_implemented_action.h"
#include <iostream>
class DB;

namespace auth{

enum Status{
    Status_Normal = 0,
    Status_Deleted = 1<<31
};

using std::string;
using std::vector;

template<typename T>
class ImplementedAction{
public:
//    static_assert // is table
    ImplementedAction():
        m_title(""), m_status(Status_Normal)
    {
    }

    ImplementedAction(const string &title):
        m_title(title), m_status(Status_Normal)
    {
    }

    ImplementedAction(const string &title, Status status):
        m_title(title), m_status(status){}

    constexpr const char *tableName() const {
        return sqlpp::name_of<T>::char_ptr();
    }


    void setTitle(const string &title){ m_title = title; }
    void setStatus(Status s){ m_status = s;}
    Status status() const { return m_status; }

    const string &title() const{ return m_title; }

    bool save(DB &db){
        static constexpr schema::t_implemented_action ia;
        bool ok = false;
        try{
            db(insert_into(ia).set(ia.c_table = tableName(), ia.c_action = m_title, ia.c_status = (int)m_status ));
            ok = true;
        }
        catch(sqlpp::exception e){
            ///TODO log exception
            std::cout << e.what();
        }

        return ok;
    }

    bool exists(DB &db) const {
        static constexpr schema::t_implemented_action ia;
        return db(sqlpp::select(sqlpp::exists(sqlpp::select(ia.c_action)
                         .from(ia)
                         .where(ia.c_table == tableName() and ia.c_action == m_title and ia.c_status == (int)m_status )
                         )
                  )
           ).front().exists;
    }

private:
    string m_title;
    Status m_status;
};

}
