#pragma once

#include "iprocessor.h"

class DB;

namespace pb{
    class ClientRequest;
    class ItemReq;
    class ItemReq_Add;
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
    void process(pb::ClientRequest &msgReq );
    void process(DB &db, pb::ClientRequest &msgReq );

private:
    void handle_add(DB &db, pb::ItemReq_Add &msg);

    void run_saveItemInDb(DB &db, pb::ItemReq_Add &msg);
};

}
}
