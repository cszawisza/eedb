#pragma once

#include "iprocessor.h"
#include "idatabase.h"

namespace core {
namespace parsers {

class User : public MessageHandler, public DatabasePool
{
public:
    User() {}
    virtual ~User() {}
};

}
}
