#pragma once

#include "iprocessor.h"

class DB;

namespace eedb {
namespace pu {

class CategoryPU : public IMessageProcessingUnit
{
public:
    CategoryPU() {}
    virtual ~CategoryPU() {}

    // MessageHandler interface
public:
    void process( IClientRequest *msgReq );
    void process(DB &db, IClientRequest *msgReq ) override;

private:

//    void handle_add(DB &db, pb::CategoryReq_Add &msg);
//    void handle_get(DB &db, pb::CategoryReq_Get &msg);
};

}
}
