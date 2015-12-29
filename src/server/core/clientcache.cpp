#include "clientcache.h"

ClientCache::ClientCache()
{
}

int UserData::uid() const
{
    return m_uid;
}

void UserData::setUid(int uid)
{
    m_uid = uid;
}
