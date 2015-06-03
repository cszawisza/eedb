project(eedb)

add_definitions(-std=c++11)

cmake_minimum_required(VERSION 3.0.2)
#aux_source_directory(. SRC_LIST)

add_subdirectory(externals)
add_subdirectory(generated)
add_subdirectory(src)

