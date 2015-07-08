add_subdirectory(Source)
add_subdirectory(Header)
add_subdirectory(Forms)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Header)

add_executable( Client main.cpp)
target_link_libraries( Client qt_app_lib)
