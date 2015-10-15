#pragma once

#include "iprocessor.h"

class DB;

namespace pb {
    class ClientRequest;
    class CategoryReq_Add;
    class CategoryReq_Get;
}

namespace eedb {
namespace pu {

class CategoryPU : public IMessageProcessingUint
{
public:
    CategoryPU() {}
    virtual ~CategoryPU() {}

    // MessageHandler interface
public:
    void process(pb::ClientRequest &msgReq );
    void process(DB &db, pb::ClientRequest &msgReq ) override;

private:

    void handle_add(DB &db, pb::CategoryReq_Add &msg);
    void handle_get(DB &db, pb::CategoryReq_Get &msg);
};

}
}
