#pragma once

#include <boost/variant.hpp>
#include <boost/optional.hpp>
#include <boost/none.hpp>

#include <string>
#include <array>
#include <type_traits>

#include <QString>

namespace data{

using Int64 = int64_t;
using UInt64 = uint64_t;
using UID = uint64_t;
using Bytes = std::string;
using String = std::string;
using Email = std::string;

enum Status{

};

struct Credentials{
    boost::variant<
        boost::blank,
        String,
        UID
    > data;
};

}
