#pragma once

#include <QSharedPointer>


class UserStatus{
public:
    enum Status{
        logged,
        notLogged
    };

    UserStatus():
        m_status(notLogged){
    }
    bool isLogged() const { return m_status == logged; }
    void setStatus(Status s){ m_status = s; }

private:

    Status m_status;
};

class ClientCache
{
public:
    ClientCache();
    
    UserStatus &userStatus() {
        return m_userStatus;
    }
    
private:
    UserStatus m_userStatus;
};

typedef QSharedPointer<ClientCache> SharedClientCache;
