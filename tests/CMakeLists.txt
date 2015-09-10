include_directories( ${gmock_SOURCE_DIR}/gtest/include )
include_directories( ${gmock_SOURCE_DIR}/include )

include_directories( ${ProtobufIncludePath})
INCLUDE_DIRECTORIES( ${Common_SOURCE_DIR} )
INCLUDE_DIRECTORIES( ${EEDB_SERVER_SOURCE_DIR} )
INCLUDE_DIRECTORIES( ${EEDB_SERVER_SOURCE_DIR}/core )
include_directories( ${Externals_SOURCE_DIR} )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )

INCLUDE_DIRECTORIES( ../server_lib )

set(TEST_EXECUTABLE_NAME Tests )

find_library( CPPUNIT_LIBRARY_DEBUG NAMES sqlpp-postgresql
            PATHS   /usr/lib
                    /usr/lib64
                    /usr/local/lib
                    /usr/local/lib64
            )

find_package(Qt5Core)
find_package(Qt5WebSockets)

set(MAIN_SRC main.cpp)
file(GLOB_RECURSE TESTS_SRC Test Common.hpp DbCon/* common/* server/*)
add_executable(${TEST_EXECUTABLE_NAME} ${MAIN_SRC} ${TESTS_SRC})
add_test( ${TEST_EXECUTABLE_NAME} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TEST_EXECUTABLE_NAME} )
install(TARGETS ${TEST_EXECUTABLE_NAME}
        DESTINATION bin
        CONFIGURATIONS Debug )

IF ( CMAKE_BUILD_TYPE STREQUAL "Coverage")
    SETUP_TARGET_FOR_COVERAGE_COBERTURA( Server_cover ${TEST_EXECUTABLE_NAME} cover/server)
ENDIF() # CMAKE_BUILD_TYPE STREQUAL "Coverage"

target_link_libraries(Tests gtest eedb_lib pq)
