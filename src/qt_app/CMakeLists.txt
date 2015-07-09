add_subdirectory(Source)
add_subdirectory(Include)
add_subdirectory(Forms)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Include)

add_executable( Client main.cpp)
target_link_libraries( Client qt_app_lib)
