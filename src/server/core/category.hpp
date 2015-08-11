#pragma once

#include "iprocessor.h"
#include "group.pb.h"

class DB;

namespace eedb {
namespace handlers {

using namespace pb;

class Category : public MessageHandler
{
public:
    Category() {}
    virtual ~Category() {}

    // MessageHandler interface
public:
    void process(pb::ClientRequest &msgReq );
    void process(DB &db, pb::ClientRequest &msgReq );

private:

};

}
}
