find_package(Qt5Test REQUIRED)
FILE(GLOB TEST_SRC_FILES *.cpp)
FILE(GLOB TEST_MOCK_FILES Mocks/*.hpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Mocks)
include_directories(../Include)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})
INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR}/src/qt_app )
include_directories(${ProtobufIncludePath})

add_executable(ClientTests ${TEST_SRC_FILES} ${TEST_MOCK_FILES})
target_link_libraries(ClientTests Common client_lib ${PROTOBUF_LITE_LIBRARY} gtest gmock Qt5::Widgets Qt5::WebSockets Qt5::Core Qt5::Test)
