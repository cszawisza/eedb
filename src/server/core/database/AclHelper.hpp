#pragma once

#include "idatabase.h"
#include "common.pb.h"

namespace eedb{
namespace db{

class AclHelper {
public:
    static Acl getAcl(DB &db, uint64_t objectID);
};

}
}
