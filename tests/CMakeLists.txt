include_directories( ${gmock_SOURCE_DIR}/gtest/include )
include_directories( ${gmock_SOURCE_DIR}/include )

include_directories( ${ProtobufIncludePath})
INCLUDE_DIRECTORIES( ${Common_SOURCE_DIR} )
INCLUDE_DIRECTORIES( ${EEDB_SERVER_SOURCE_DIR} )
INCLUDE_DIRECTORIES( ${EEDB_SERVER_SOURCE_DIR}/core )
include_directories( ${Externals_SOURCE_DIR} )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )

INCLUDE_DIRECTORIES( ../server_lib )

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
file(GLOB_RECURSE TESTS_SRC TestCommon.hpp common/* server/* DbCon/*)
add_executable(Tests ${MAIN_SRC} ${TESTS_SRC})

target_link_libraries(Tests gtest eedb_lib pq)
