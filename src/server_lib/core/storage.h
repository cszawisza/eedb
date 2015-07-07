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
    void process(pb::ClientRequest &msg);

private:
    void handle_add( MsgInventoryRequest_Add &msg );
    void handle_get( const MsgInventoryRequest_Get &msg);
    void handle_modify(const MsgInventoryRequest_Modify &msg);
    void handle_remove( const MsgInventoryRequest_Remove &msg );
    void handle_addShelf( const MsgInventoryRequest_AddShelf &msg);

    void insertStorage(DB &db, const MsgInventoryRequest_Add &msgReq);
    void linkInventoryWithUser(DB &db, quint64 inventoryId);
    quint64 insertInventory(DB &db, const MsgInventoryRequest_Add &msgReq);

    void addResp(bool isError, int err_code){
//        pb::ServerResponse res = pb::ServerResponse::default_instance();
//        auto code = res.add_codes();
//        code->set_error(isError);
//        code->set_code(err_code);
//        addResponse(res);
    }
    quint64 doInsert(DB &db, const MsgInventoryRequest_Add &msgReq);
};

}
}
