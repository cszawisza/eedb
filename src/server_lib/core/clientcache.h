#pragma once

enum Status{
    logged,
    notLogged
};


class UserStatus{
public:
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

