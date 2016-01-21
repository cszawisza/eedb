find_package( Qt5Core REQUIRED)
find_package( Qt5WebSockets REQUIRED)
find_package( Protobuf REQUIRED)

add_definitions(-DQT_NO_CAST_FROM_ASCII)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

link_libraries( Qt5::WebSockets Qt5::Core ${PROTOBUF_LITE_LIBRARY} )
include_directories( ${Externals_SOURCE_DIR} )

add_subdirectory(common)
include_directories( ${ProtobufIncludePath} )

optional_add_subdirectory(qt_app)
optional_add_subdirectory(server)


