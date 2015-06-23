#pragma once

#include "iprocessor.h"
#include "idatabase.h"

#include "pb_cpp/storage.pb.h"

namespace eedb {
namespace handlers {

using namespace storage;
class Storage : public MessageHandler
{
public:
    Storage() {}
    virtual ~Storage() {}

    // MessageHandler interface
public:
    void process(protbuf::ClientRequest &msg);

private:
    void handle_add(const MsgStorageRequest_Add &msgReq );
    void handle_get( const MsgStorageRequest_Get &msg);
    void handle_modify(const MsgStorageRequest_Modify &msg);
    void handle_remove( const MsgStorageRequest_Remove &msg );
};

}
}
