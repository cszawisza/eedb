include_directories( ${gmock_SOURCE_DIR}/gtest/include )
include_directories( ${gmock_SOURCE_DIR}/include )

include_directories(${ProtobufIncludePath})
INCLUDE_DIRECTORIES( ${Common_SOURCE_DIR} )
INCLUDE_DIRECTORIES( ${EEDB_SERVER_SOURCE_DIR} )

find_library( CPPUNIT_LIBRARY_DEBUG NAMES sqlpp-postgresql
            PATHS   /usr/lib
                    /usr/lib64
                    /usr/local/lib
                    /usr/local/lib64
            )

find_package(Qt5Core)
find_package(Qt5WebSockets)

set(MAIN_SRC main.cpp)
#
file(GLOB_RECURSE TESTS_SRC common.h DbCon/* common/* server/* )
add_executable(Tests ${MAIN_SRC} ${TESTS_SRC})

target_link_libraries(Tests gtest eedb_lib pq)
