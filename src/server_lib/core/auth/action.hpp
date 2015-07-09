#pragma once
#include <string>

class DB;

namespace auth {

using std::string;
enum ObjectType{
    Object = 1,
    Table = 0
};

class Action{
public:
    Action(const string &title, ObjectType object ):
        m_title(title), type(object)
    {
    }

    inline void setIsObject();
    inline void setIsTable();
    inline void setTitle( const string &title );

    inline const string &title() const;
    inline bool applyToObject() const;
    inline bool applyToTable() const;

    bool save(DB &db);
    bool actionExists(DB &db) const;

private:
    string m_title;
    ObjectType type;
};

void Action::setIsObject(){
    type = Object;
}

void Action::setIsTable(){
    type = Table;
}

void Action::setTitle(const std::string &title){
    m_title = title;
}

const std::string &Action::title() const {
    return m_title;
}

bool Action::applyToObject() const {
    return (bool) type;
}

bool Action::applyToTable() const{
    return ! applyToObject();
}
}
