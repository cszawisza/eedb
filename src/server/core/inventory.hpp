#pragma once

#include "iprocessor.h"
#include "database/idatabase.h"

#include "inventory.pb.h"
#include "inventory_operation.pb.h"

namespace eedb {
namespace handlers {

using namespace pb;
class Inventory : public MessageHandler
{
public:
    Inventory() {}
    virtual ~Inventory() {}

    // MessageHandler interface
public:
    void process(DB &db, pb::ClientRequest &msg);
    void process(pb::ClientRequest &msg);

private:
    void handle_add(DB &db, MsgInventoryRequest_Add &msg );
    void handle_get(DB &db, MsgInventoryRequest_Get &msg);
    void handle_modify(const MsgInventoryRequest_Modify &msg);
    void handle_remove( const MsgInventoryRequest_Remove &msg );
    void handle_addShelf( const MsgInventoryRequest_AddShelf &msg);

    void insertInventory(DB &db, MsgInventoryRequest_Add &msg);

    void addErrorCode( MsgInventoryResponse_Error code ){
        m_response.mutable_msginventoryres()->add_code(code);
    }

    pb::ServerResponse m_response;
};

}
}
