project(EEDB_Common_UT)

file(GLOB_RECURSE TEST_SRC_FILES *.cpp *.hpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Mocks)
include_directories(../DataStructures)
INCLUDE_DIRECTORIES(../DataStructures/Adaptors )
include_directories(../)
include_directories( ${ProtobufIncludePath} )
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})

add_executable(CommonTests ${TEST_SRC_FILES} )
target_link_libraries( CommonTests Common gtest gmock)
