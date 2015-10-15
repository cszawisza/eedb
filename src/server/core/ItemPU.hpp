#pragma once

#include "iprocessor.h"
#include "item.pb.h"

class DB;

namespace pb{
    class ClientRequest;
    class ItemRequest;
    class ItemRequest_Add;
}

namespace eedb {
namespace pu {

class ItemPU : public IMessageProcessingUint
{
public:
    ItemPU();
    virtual ~ItemPU() {}

    // MessageHandler interface
public:
    void process(ClientRequest &msgReq );
    void process(DB &db, ClientRequest &msgReq );

private:
    void handle_add(DB &db, pb::ItemRequest_Add &msg);
};

}
}
