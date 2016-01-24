project(EEDB_Client_UT)
find_package(Qt5Test REQUIRED)
FILE(GLOB TEST_SRC_FILES *.cpp)
FILE(GLOB TEST_MOCK_FILES Mocks/*.hpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Mocks)
include_directories(../Include)

include_directories( ${Common_SOURCE_DIR} )
include_directories( ${Common_SOURCE_DIR}/DataStructures )

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})
include_directories(${CMAKE_BINARY_DIR}/src/qt_app )


add_definitions(-DQT_NO_DEBUG_OUTPUT)
add_definitions(-DQT_NO_WARNING_OUTPUT)
#add_compile_options(-DQT_NO_DEBUG_OUTPUT)
#add_compile_options(-DQT_NO_WARNING_OUTPUT)

#files containing Q_OBJECT makro
set(QT_HEADERS
    Mocks/ISocketMock.hpp
    Mocks/ILoginVerificatorMock.hpp
    Mocks/CommunicationManagerMock.hpp
)

QT5_WRAP_CPP(GUI_MOC_SRCS ${QT_HEADERS})

add_executable(ClientTests main.cpp ${TEST_SRC_FILES} ${TEST_MOCK_FILES} ${GUI_MOC_SRCS})
target_link_libraries( ClientTests Common  ProtobufAdapter client_lib gtest gmock Qt5::Core Qt5::Widgets Qt5::Test)
