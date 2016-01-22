#pragma once

#include <boost/none.hpp>
#include <boost/optional.hpp>

template<typename T>
class Optional : public boost::optional<T>{
public:
    Optional():
        boost::optional<T>(){}

    Optional( boost::none_t val ):
        boost::optional<T>(val){}

    Optional( T val ):
        boost::optional<T>(val){}
};
