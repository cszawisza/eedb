#pragma once

#include "iprocessor.h"

class DB;
namespace requests{
namespace category{
class IAdd;
class IGet;
}
}

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

    void handle_add(DB &db, const requests::category::IAdd &msg);
    void handle_get(DB &db, const requests::category::IGet &msg);
};

}
}
