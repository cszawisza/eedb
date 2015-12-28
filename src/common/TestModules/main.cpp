#include "gtest/gtest.h"
#include "spdlog/spdlog.h"

volatile uint times=0;
volatile uint total=0;
volatile uint maxDepth=0;
volatile uint maxAllocatedAtOnce=0;
volatile uint allAllocatedAtOnce=0;

void* myAlloc(size_t sz) {
    times++;
    total+=sz;
    allAllocatedAtOnce++;

    if(allAllocatedAtOnce>maxDepth)
        maxDepth=allAllocatedAtOnce;

    if(sz>maxAllocatedAtOnce)
        maxAllocatedAtOnce=sz;

    void* m = malloc(sz);
    return m;
}

void myFree(void* m) {
    free(m);
    allAllocatedAtOnce--;
}

inline void* operator new     ( size_t size ) { return myAlloc( size ); }
inline void* operator new[]   ( size_t size ) { return myAlloc( size ); }
inline void  operator delete  ( void* ptr   ) { myFree( ptr ); }
inline void  operator delete[]( void* ptr   ) { myFree( ptr ); }

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
//    testing::GTEST_FLAG(filter) = "UserDataAddResTests*";

    auto ret = RUN_ALL_TESTS();
    printf("allocated %d bytes in %d allocations\n",total, times);
    printf("max number of allocated elements %d\n", maxDepth);
    printf("biggest single alloc %d\n", maxAllocatedAtOnce);
    return ret;
}
