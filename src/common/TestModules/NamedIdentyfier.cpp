#include "gtest/gtest.h"
#include "StructuresCommon.hpp"


static constexpr auto id1 = ActionId(1, "some action");
static constexpr auto id2 = ActionId(2, "some other action");
static constexpr auto id3 = ActionId(2, "some other action");



TEST(NamedIdentyfierTest, staticAsserts ){
    static_assert(id1 != id2, "id assert");
    static_assert(id3 == id2, "id assert");
    static_assert(id1 < id2, "id assert");
    static_assert(id1 <= id2, "id assert");
    static_assert(id2 > id1, "id assert");
    static_assert(id2 >= id1, "id assert");
    static_assert(id2 <= id2, "id assert");
    static_assert(id1 >= id1, "id assert");
}

TEST(NamedIdentyfierTest, staticAssertsInts ){
    static_assert(id1 != 2, "id assert");
    static_assert(id3 == 2, "id assert");
    static_assert(id1 < 2, "id assert");
    static_assert(id1 <= 2, "id assert");
    static_assert(id2 > 1, "id assert");
    static_assert(id2 >= 1, "id assert");
    static_assert(id2 <= 2, "id assert");
    static_assert(id1 >= 1, "id assert");
}
