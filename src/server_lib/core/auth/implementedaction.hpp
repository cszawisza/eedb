#pragma once
#include <sqlpp11/sqlpp11.h>
#include "utils/sqlpp_helper.hpp"
#include "core/idatabase.h"
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

class ImplementedAction{
public:
//    static_assert // is table
    ImplementedAction():
        m_title(""), m_status(Status_Normal), m_tablename("")
    {
    }
    ImplementedAction(const string &title):
        m_title(title), m_status(Status_Normal), m_tablename("")
    {
    }
    ImplementedAction(const string &title, Status status):
        m_title(title), m_status(status), m_tablename("")
    {
    }
    ImplementedAction(const string &title, Status status, const string &related_table):
        m_title(title), m_status(status), m_tablename(related_table)
    {
    }

    template<typename T>
    void setRelatedTable(){
        m_tablename = sqlpp::tableName<T>();
    }

    string tableName() const {
        return m_tablename;
    }

    void setTitle(const string &title){
        m_title = title;
    }

    const string &title() const{
        return m_title;
    }

    void setStatus(Status s){
        m_status = s;
    }
    Status status() const { return m_status; }

    bool save(DB &db);

    bool exists(DB &db) const;

private:
    string m_tablename;
    string m_title;
    Status m_status;
};

}
