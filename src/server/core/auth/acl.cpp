#include "acl.hpp"

namespace auth{
bool AccesControl::checkBasicPerms(DB &db, const string &action, uint64_t objectid){
    // check if root, and return true if so (root can everything :) )
    if(m_userId == rootId )
        return true;

    protobuf::Acl objectAcl;

    ///TODO
    /// 1: save the acl info in chace and update it only once a while to prevent db roundtrips
    ///    according to this a simple 'todo' list
    ///     1. give Acl acces to thread cache
    ///     2. check is acl has ben already taken from database and valid
    ///     3. check date od databese query
    ///     4. check acl
    ///     5. save value in cache
    /// 2: Change this to event based operations
    ///     One thread changes object's acl info, and propagate it by the whole serwer (each thread)
    /// 3: Provide a GLOBAL cache, and synchronize writes to that one object in whole system(and take 1)
    ///     but without date chacking

    schema::stat acl;
    auto aclInfo = db( sqlpp::select( sqlpp::all_of(acl) )
                       .from(acl)
                       .where( acl.uid == m_userId || acl.uid == objectid ) );
    if(aclInfo.empty())
        return false; // no object found

    while(!aclInfo.empty()){
        if(aclInfo.front().uid == m_userId)
            readAclFromData(m_userAcl, aclInfo);
        else
            readAclFromData(objectAcl, aclInfo);
        aclInfo.pop_front();
    }

    if ((m_userAcl.group() & groupsroot) != 0)
        return true;
    if( (action == "read") && (((objectAcl.unixperms() & other_read) != 0) || (((objectAcl.unixperms() & owner_read) != 0) && objectAcl.owner() == m_userId ) || (( (objectAcl.unixperms() & group_read) != 0) && ( (objectAcl.group() & m_userAcl.group()) != 0 )))  ){
        return true;
    }
    if( (action == "write") && (((objectAcl.unixperms() & other_write) != 0) || (((objectAcl.unixperms() & owner_write) != 0) && objectAcl.owner() == m_userId ) || (( (objectAcl.unixperms() & group_write) != 0) && ( (objectAcl.group() & m_userAcl.group()) != 0 )))  ){
        return true;
    }
    if( (action == "delete") && (((objectAcl.unixperms() & other_delete) != 0) || (((objectAcl.unixperms() & owner_delete) != 0) && objectAcl.owner() == m_userId ) || (( (objectAcl.unixperms() & group_delete) != 0) && ( (objectAcl.group() & m_userAcl.group()) != 0 )))  ){
        return true;
    }

    return false;
}
}
