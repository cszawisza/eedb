#pragma once

#include <QSharedPointer>
#include <string>

#include "user.pb.h"
#include "common.pb.h" // for acl

using namespace std;

struct UserData{
    qint64 id;
    string name;
};

class User{
public:
    enum Status{
        logged,
        notLogged
    };

    User():
        m_status(notLogged){}
    bool isLogged() const { return m_status == logged; }
    void setIsLogged() { setStatus(logged);}
    void setStatus(Status s){ m_status = s; }

    UserData &data(){ return m_data; }
private:
    UserData m_data;
    Status m_status;
};

class ClientCache
{
public:
    ClientCache();
    
    User &user() {return m_userStatus;}
    
private:
    User m_userStatus;
};

typedef QSharedPointer<ClientCache> SharedClientCache;
