#include <gtest/gtest.h>

#include <QElapsedTimer>

#include "../common/utils/CTcrc32.hpp"

//TEST( CompileTime, crc32 ){
//    EXPECT_NE(0, CT_CRC32("Some compile time string"));
//}

//TEST( CompileTime, vsDynamicCalculatedCRC ){
//    std::string str = "Some compile time string";
//    auto ct = CT_CRC32("Some compile time string");
//    auto dy = RT_CRC32(str);
//    EXPECT_EQ(ct, dy);
//}

//TEST(ComplieTime, benchmark){
//    QElapsedTimer timer;
//    quint64 timeTotal = 0;

//    timer.start();
//    for(int i=0;i<10;i++){
//        timeTotal += CT_CRC32("Some compile time stringSome compile time stringSome compile time stringSome compile time stringSome compile time stringSome compile time stringSome compile time stringSome compile time stringSome compile time stringSome compile time stringSome compile time stringSome compile time string");
//    }

//    std::cout << "\nCT: " << timer.nsecsElapsed()  << " in " << timeTotal;
//    timeTotal = 0;
//    timer.restart();
//    for(int i=0;i<10;i++){
//        timeTotal += RT_CRC32("Some compile time stringSome compile time stringSome compile time stringSome compile time stringSome compile time stringSome compile time stringSome compile time stringSome compile time stringSome compile time stringSome compile time stringSome compile time stringSome compile time string");
//    }

//    std::cout << "\nRT: " << timer.nsecsElapsed() << " in " << timeTotal;
//}
