#pragma once

#include "iprocessor.h"

namespace protobuf{
    class ClientRequest;
    class ServerResponse;
    class MsgInventoryRequest_Add;
    class MsgInventoryRequest_Get;
    class MsgInventoryRequest_Modify;
    class MsgInventoryRequest_Remove;
    class MsgInventoryRequest_AddShelf;
}

namespace eedb {
namespace pu {

class InventoryPU : public IMessageProcessingUnit
{
public:
    InventoryPU() {}
    virtual ~InventoryPU() {}

    // MessageHandler interface
public:
    void process(DB &db, protobuf::ClientRequest &msg);
    void process(protobuf::ClientRequest &msg);

private:
    void handle_add(DB &db, protobuf::MsgInventoryRequest_Add &msg );
    void handle_get(DB &db, protobuf::MsgInventoryRequest_Get &msg);
    void handle_modify(const protobuf::MsgInventoryRequest_Modify &msg);
    void handle_remove( const protobuf::MsgInventoryRequest_Remove &msg );
    void handle_addShelf( DB &db, protobuf::MsgInventoryRequest_AddShelf &msg);

    void insertInventory(DB &db, protobuf::MsgInventoryRequest_Add &msg);

//    void addErrorCode( pb::MsgInventoryResponse_Error code, pb::ServerResponse *res );
};

}
}
