#pragma once

#include "iprocessor.h"
#include "item.pb.h"

class DB;

namespace eedb {
namespace handlers {

using namespace pb;

class ItemProcessor : public MessageHandler
{
public:
    ItemProcessor();
    virtual ~ItemProcessor() {}

    // MessageHandler interface
public:
    void process(pb::ClientRequest &msgReq );
    void process(DB &db, pb::ClientRequest &msgReq );

private:
    void handle_add   (DB &db, ItemRequest_Add    &msg);
};

}
}
