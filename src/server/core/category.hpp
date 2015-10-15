#pragma once

#include "iprocessor.h"
#include "category.pb.h"

class DB;

namespace eedb {
namespace pu {

using namespace pb;

class Category : public IMessageProcessingUint
{
public:
    Category() {}
    virtual ~Category() {}

    // MessageHandler interface
public:
    void process(pb::ClientRequest &msgReq );
    void process(DB &db, pb::ClientRequest &msgReq ) override;

private:

    void handle_add(DB &db, CategoryReq_Add &msg);
    void handle_get(DB &db, CategoryReq_Get &msg);
};

}
}
