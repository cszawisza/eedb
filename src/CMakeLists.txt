find_package( Qt5Core REQUIRED)
find_package( Qt5WebSockets REQUIRED)
find_package( Protobuf REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_subdirectory(common)
add_subdirectory(qt_app)
add_subdirectory(server_lib)
add_subdirectory(server_app)
