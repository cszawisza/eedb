#pragma once

#include "idatabase.h"
#include "common.pb.h"

#include <boost/optional.hpp>

using boost::optional;

namespace eedb{
namespace db{

class AclHelper {
public:
    static optional<Acl> getAcl(DB &db, uint64_t objectID);
};

}
}
