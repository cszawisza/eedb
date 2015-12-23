#pragma once

#include "iprocessor.h"

namespace pb{
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
    void process(DB &db, pb::ClientRequest &msg);
    void process(pb::ClientRequest &msg);

private:
    void handle_add(DB &db, pb::MsgInventoryRequest_Add &msg );
    void handle_get(DB &db, pb::MsgInventoryRequest_Get &msg);
    void handle_modify(const pb::MsgInventoryRequest_Modify &msg);
    void handle_remove( const pb::MsgInventoryRequest_Remove &msg );
    void handle_addShelf( DB &db, pb::MsgInventoryRequest_AddShelf &msg);

    void insertInventory(DB &db, pb::MsgInventoryRequest_Add &msg);

//    void addErrorCode( pb::MsgInventoryResponse_Error code, pb::ServerResponse *res );
};

}
}
