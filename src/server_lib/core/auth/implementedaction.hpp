#pragma once

#include <sqlpp11/sqlpp11.h>

class DB;

namespace auth{

enum Status{
    Normal = 0
};

using std::string;

template<typename T>
class ImplementedAction{
public:
//    static_assert // is table
    ImplementedAction(const string &action, Status status):
        m_action(action), m_status(status){}

    constexpr const char *tableName() const {
        return sqlpp::name_of<T>::char_ptr();
    }

    const string &actionTitle() const{
        return m_action;
    }

    bool addImplementedAction(DB &db){
//        return addImpl(db, tableName() );
        return true;
    }

    bool implementedActionExists(DB &db){
//        return existsImpl(db, tableName());
        return true;
    }

private:
    string m_action;
    Status m_status;
};

}
