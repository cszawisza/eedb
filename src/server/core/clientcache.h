#pragma once

#include <QSharedPointer>
#include <string>

#include "user.pb.h"
#include "common.pb.h" // for acl

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
        m_basicData.Clear();
        m_acl.Clear();
    }
    bool isOnline() const { return m_status == UserOnline; }
    bool isOffline() const { return m_status == UserOffline; }
    void goOnline() { m_status = UserOnline; }
    void goOffLine() { m_status = UserOffline; }

    uint64_t id() const {
        if(m_basicData.has_id())
            return m_basicData.id();
        else
            return 0;
    }

    pb::UserBasic *mutable_basic(){
        return &m_basicData;
    }

    pb::Acl *mutable_acl(){
        return &m_acl;
    }

private:
    Status m_status;
    pb::UserBasic m_basicData;
    pb::Acl m_acl;
};

class ClientCache
{
public:
    ClientCache();
};

using SharedUserData = QSharedPointer<UserData>;
