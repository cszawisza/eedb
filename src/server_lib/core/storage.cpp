#include "storage.h"
void eedb::handlers::Storage::process(protbuf::ClientRequest &msg )
{
    // Check if this is the message that handler wants
    Q_ASSERT( msg.data_case() == protbuf::ClientRequest::kMsgStorageReq );
    Q_ASSERT( msg.has_msgstoragereq() );

    if (!cache()->user().isLogged())
        return;

//    db.takeFromPool();
    auto req = msg.msgstoragereq();

    using storage::MsgStorageRequest;
    MsgStorageRequest::DataCase msgType = req.data_case();
    switch ( msgType ) {
    case MsgStorageRequest::kAdd:
        handle_add( req.add() );
        break;
    case MsgStorageRequest::kGet:
        handle_get( req.get() );
        break;
    case MsgStorageRequest::kRemove:
        handle_remove( req.remove() );
        break;
    case MsgStorageRequest::kModify:
        handle_modify( req.modify() );
        break;
    case MsgStorageRequest::DATA_NOT_SET:
        // send server error
        break;
    }

//    db.pushToPool();
}

void eedb::handlers::Storage::handle_add(const storage::MsgStorageRequest_Add &msgReq)
{

}

void eedb::handlers::Storage::handle_get(const storage::MsgStorageRequest_Get &msg)
{

}

void eedb::handlers::Storage::handle_modify(const storage::MsgStorageRequest_Modify &msg)
{

}

void eedb::handlers::Storage::handle_remove(const storage::MsgStorageRequest_Remove &msg)
{

}
