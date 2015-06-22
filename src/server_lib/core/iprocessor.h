#pragma once
// interface allowing to create message parsers
#include <QObject>
#include <QSharedPointer>
#include <QDebug>
#include <QSharedPointer>
#include "pb_cpp/message_conteiner.pb.h"
#include "clientcache.h"
#include "idatabase.h"
#include "acl.h"

using protbuf::ClientRequest;
using protbuf::ClientRequests;
/**
 * @brief The IProcessor class
 */

class MessageHandler
{
public:
    typedef QSharedPointer<protbuf::ClientRequests> SharedRequests;
    typedef QSharedPointer<protbuf::ServerResponses> SharedResponses;
    MessageHandler(){}
    virtual ~MessageHandler(){;}

    /// set database connection
    void setDb( DbConnection &con ){
        ///FIXME
//        db.setDatabaseConnection( unique_ptr<DbConnection>(&con) );
    }

    /// get db

    /// get ouptut data
    protbuf::ServerResponse getLastResponse(){
        return m_outputFrame->response(m_outputFrame->response_size()-1);
    }

    void setOutputData( SharedResponses frame ){
        m_outputFrame.swap( frame );
    }

    /**
     * @brief setClientCache
     * @param cache: sets a pointer to common cache (containing user status information and session stuf)
     */
    void setClientCache( SharedClientCache cache){
        m_cache.swap(cache);
    }

    /**
     * @brief process data given in setWorkingCapsule;
     */
    virtual void process(protbuf::ClientRequest &req){
        auto msg = m_outputFrame->add_response();
        msg->CopyFrom( protbuf::ServerResponse::default_instance() );
        msg->set_responseid( req.requestid() );
        ResponseCode *codes = msg->mutable_msgserverresponse()->add_codes();
        codes->set_error(true);
        codes->set_code( protbuf::ServerErrorCodes::Error_MsgUnknown );
    }

protected:

    const bool addResponse( const protbuf::ServerResponse &resp ){
        if(!m_outputFrame)
            m_outputFrame = SharedResponses(new protbuf::ServerResponses);
        m_outputFrame->add_response()->MergeFrom(resp);
    }

    SharedClientCache cache() {
        if(!m_cache)
            m_cache = SharedClientCache(new ClientCache );
        return m_cache;
    }

    bool canTakeAction( string action, quint64 objectid)
    {
        constexpr int owner_read    = 1<<8;
        constexpr int owner_write   = 1<<7;
        constexpr int owner_delete  = 1<<6;
        constexpr int group_read    = 1<<5;
        constexpr int group_write   = 1<<4;
        constexpr int group_delete  = 1<<3;
        constexpr int other_read    = 1<<2;
        constexpr int other_write   = 1<<1;
        constexpr int other_delete  = 1<<0;

        constexpr int groupsroot = 1;

        int usergroups = 0;
        quint64 userid = cache()->user().data().id;

        // check if root
        if(userid == 1 )
            return true;

        vector<string> result;

        schema::t_acl acl;
        schema::t_users user;
        schema::t_action act;
        schema::t_implemented_action ia;
        schema::t_privilege pr;

        DB db;
        // always check usergroups, or read from cache?
        auto aclInfo = db( sqlpp::select( sqlpp::all_of(acl) )
                                   .from(acl)
                                   .where( acl.c_uid == userid || acl.c_uid == objectid ) );
        if(aclInfo.empty())
            return false; // no object found

        while(!aclInfo.empty()){
            if(true){

            }
            aclInfo.pop_front();
        }

        string tablename = "t_users";

        if ((usergroups & groupsroot) != 0)
            return true;

        auto res = db( sqlpp::select().flags(sqlpp::distinct).columns(act.c_title)
                       .from(act
                             .inner_join(acl).on(acl.c_uid == objectid)
                             .inner_join(ia).on(ia.c_action == act.c_title and ia.c_table == tablename and (ia.c_status == 0 or ((ia.c_status & acl.c_status) != 0)) )
                             .left_outer_join(pr).on(pr.c_related_table == tablename and pr.c_action == act.c_title and ((pr.c_type == "object" and pr.c_related_uid == objectid) or (pr.c_type == "global") or ( (pr.c_role == "self") and sqlpp::verbatim<sqlpp::boolean>((userid == objectid) ? "TRUE " : "FALSE ") and sqlpp::verbatim<sqlpp::boolean>( (tablename == "users") ? "TRUE " : "FALSE "))))
                             )
                       .where(
                           (act.c_title == action) and
                           act.c_apply_object
                           and ((
                                    (    act.c_title == "read"   and (( (acl.c_unixperms & other_read)   != 0 ) or (( (acl.c_unixperms & owner_read)   != 0)  and acl.c_owner == userid ) or (( (acl.c_unixperms & group_read)   != 0) and ( (acl.c_group & usergroups) != 0 ))) )
                                    or ( act.c_title == "write"  and (( (acl.c_unixperms & other_write)  != 0 ) or (( (acl.c_unixperms & owner_write)  != 0)  and acl.c_owner == userid ) or (( (acl.c_unixperms & group_write)  != 0) and ( (acl.c_group & usergroups) != 0 ))) )
                                    or ( act.c_title == "delete" and (( (acl.c_unixperms & other_delete) != 0 ) or (( (acl.c_unixperms & owner_delete) != 0)  and acl.c_owner == userid ) or (( (acl.c_unixperms & group_delete) != 0) and ( (acl.c_group & usergroups) != 0 ))) )
                                    or ( pr.c_role == "user"        and pr.c_who == userid )
                                    or ( pr.c_role == "owner"       and acl.c_owner == userid )
                                    or ( pr.c_role == "owner_group" and ((acl.c_group & usergroups) != 0))
                                    or ( pr.c_role == "group"       and ((pr.c_who & usergroups) != 0))
                                    /*or ( sqlpp::verbatim<sqlpp::boolean>(((usergroups & groupsroot) != 0) ? "TRUE " : "FALSE " ))*/ ) // we can say that wthout roundtrip to database
                                or (pr.c_role == "self"))
                           )
                       );

        for (const auto& row: res)
            result.push_back(row.c_title);

//        return result;
        return false;
    }

private:
    SharedClientCache m_cache;
    SharedResponses m_outputFrame;
};
