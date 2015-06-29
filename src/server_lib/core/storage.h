#pragma once

#include "iprocessor.h"
#include "idatabase.h"

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
    void process(protbuf::ClientRequest &msg);

private:
    void handle_add(const MsgInventoryRequest_Add &msgReq );
    void handle_get( const MsgInventoryRequest_Get &msg);
    void handle_modify(const MsgInventoryRequest_Modify &msg);
    void handle_remove( const MsgInventoryRequest_Remove &msg );
    void handle_addShelf( const MsgInventoryRequest_AddShelf &msg);

    void insertStorage(const MsgInventoryRequest_Add &msgReq);
    void linkInventoryWithUser(DB &db, bool &error, quint64 inventoryId);
    quint64 doInsert(DB &db, bool &error, const MsgInventoryRequest_Add &msgReq);
};

}
}
