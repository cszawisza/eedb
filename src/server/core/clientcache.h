#pragma once

#include <QSharedPointer>
#include <string>

using namespace std;

class UserData{
public:
    enum Status{
        UserOnline,
        UserOffline
    };

    UserData():
        m_status(UserOffline)
    {
//        m_basicData.Clear();
//        m_stat.Clear();
    }
    bool isOnline() const { return m_status == UserOnline; }
    bool isOffline() const { return m_status == UserOffline; }
    void goOnline() { m_status = UserOnline; }
    void goOffLine() { m_status = UserOffline; }

    int uid() const;
    void setUid(int uid);

private:
    Status m_status;
    int m_uid;
};

class ClientCache
{
public:
    ClientCache();
};
