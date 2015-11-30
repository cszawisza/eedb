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
using OptUInt64 = boost::optional<uint64_t>;
using UInt64 = uint64_t;
using UID = uint64_t;
using Bytes = std::string;
using String = std::string;
using NickName = std::string;
using Email = std::string;

template<typename T>
bool hasRequiredFields( const T &){ return false; }

template<typename T>
bool isValid(const T &){ return false; }

template<typename Base, typename Derived>
class Adapter;

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
