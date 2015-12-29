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

    uint64_t id() const {
//        if(m_basicData.has_id())
//            return m_basicData.id();
//        else
            return 0;
    }

    int uid() const;
    void setUid(int uid);

private:
    Status m_status;
    int m_uid;
//    protobuf::UserBasic m_basicData;
//    protobuf::Acl m_stat;
};

class ClientCache
{
public:
    ClientCache();
};

using SharedUserData = QSharedPointer<UserData>;
