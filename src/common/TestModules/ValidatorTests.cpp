#include "gtest/gtest.h"

#include "DataStructures/StructuresCommon.hpp"

namespace data {

//class BadWireData : public WireData{};
//class GoodWireData : public WireData{};

//template<>
//class Validator<GoodWireData> {
//    bool isInitialized() const {
//        return true;
//    }
//};

///TODO force template specializations
TEST(Validator, staticAsserts){
//   static_assert( Validator<BadWireData>::value == false, "fake data shoud fail");

}

}
