include_directories( ${gmock_SOURCE_DIR}/gtest/include )
include_directories( ${gmock_SOURCE_DIR}/include )

INCLUDE_DIRECTORIES( ${Common_SOURCE_DIR}/messages )
INCLUDE_DIRECTORIES( ${Common_SOURCE_DIR} )
INCLUDE_DIRECTORIES( ${EEDB_SERVER_SOURCE_DIR} )

find_package(Qt5Core)
find_package(Qt5WebSockets)

set(MAIN_SRC main.cpp)

file(GLOB_RECURSE TESTS_SRC common/* server/* )
add_executable(Tests ${MAIN_SRC} ${TESTS_SRC})
target_link_libraries(Tests Common eedb_lib gtest Qt5::Core )
