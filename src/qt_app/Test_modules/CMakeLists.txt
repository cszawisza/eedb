FILE(GLOB TEST_SRC_FILES *.cpp)
FILE(GLOB TEST_MOCK_FILES/Mocks/*.hpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Mocks)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})

add_executable(ClientTests ${TEST_SRC_FILES} ${TEST_MOCK_FILES})
target_link_libraries(ClientTests gtest gmock)
