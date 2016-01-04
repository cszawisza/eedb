#include <gtest/gtest.h>

#include "utils/Optional.hpp"

TEST(OptionalTests, pointer){
    Optional<int> sut;

    EXPECT_FALSE(sut);
    EXPECT_FALSE(sut.is_initialized());
}

TEST(OptionalTests, initializeByNone ){
    Optional<int> sut = boost::none;

    EXPECT_FALSE(sut);
    EXPECT_FALSE(sut.is_initialized());
}

TEST(OptionalTests, initializeByValue ){
    auto val = new int;
    Optional<int*> sut= val;

    EXPECT_TRUE(sut);
    EXPECT_TRUE(sut.is_initialized());

    delete val;
}

TEST(OptionalTests, setValue){
    auto val = new std::string;
    Optional<std::string*> sut = val;

//    sut = std::string("asdf");

//    EXPECT_EQ(sut->, "asdf");

    delete val;
}
