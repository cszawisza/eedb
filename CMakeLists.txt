project(eedb)

add_definitions(-std=c++11 -Wswitch )

cmake_minimum_required(VERSION 3.0.2)
#aux_source_directory(. SRC_LIST)

add_subdirectory(externals)
add_subdirectory(src)

