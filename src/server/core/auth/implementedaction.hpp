#pragma once
#include <sqlpp11/sqlpp11.h>
#include "utils/sqlpp_helper.hpp"
#include "database/idatabase.h"
#include "sql_schema/implemented_action.h"
#include <iostream>
#include <sqlpp11/sqlpp11.h>

class DB;

namespace auth{

enum ObjectState{
    State_Normal = 0,
    State_Hidden = 1<<2,
    State_Deleted = 1<<3,
    State_BeingModified = 1<<4
};

using std::string;
using std::vector;

class ImplementedAction{
public:
//    static_assert // is table
    ImplementedAction():
        m_title(""), m_status(State_Normal), m_tablename("")
    {
    }
    ImplementedAction(const string &title):
        m_title(title), m_status(State_Normal), m_tablename("")
    {
    }
    ImplementedAction(const string &title, ObjectState state):
        m_title(title), m_status(state), m_tablename("")
    {
    }
    ImplementedAction(const string &title, ObjectState status, const string &related_table):
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

    void setStatus(ObjectState s){
        m_status = s;
    }
    ObjectState status() const { return m_status; }

    bool save(DB &db);

    bool exists(DB &db) const;

private:
    string m_title;
    ObjectState m_status;
    string m_tablename;
};

}
