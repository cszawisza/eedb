#include <gtest/gtest.h>

#include <QElapsedTimer>

#include "../common/utils/CTcrc32.hpp"

TEST( CompileTime, crc32 ){
    EXPECT_NE(0, CT_CRC32("Some compile time string"));
}

TEST( CompileTime, vsDynamicCalculatedCRC ){
    std::string str = "Some compile time string";
    auto ct = CT_CRC32("Some compile time string");
    auto dy = RT_CRC32(str);
    EXPECT_EQ(ct, dy);
}
