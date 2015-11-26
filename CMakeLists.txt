project(eedb)
cmake_minimum_required(VERSION 3.0.2)

set (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
enable_testing()

#defines code ceverage
include(CodeCoverage)

# defines a macro: optional_add_subdirectory
include(OptionalAddDirectory)

if(NOT MSVC)
    add_definitions( -std=c++1y )
    include_directories( /usr/local )

    if ( CMAKE_BUILD_TYPE STREQUAL "Coverage")
        include(CodeCoverage)
        execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory cover)
        add_definitions( -fprofile-arcs -ftest-coverage -fPIC )
        link_libraries( gcov )
    endif() # CMAKE_BUILD_TYPE STREQUAL "Coverage"

    if ( CMAKE_BUILD_TYPE STREQUAL "Release" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo" )
        add_definitions(  -Wall -Wextra  -Wswitch )
        add_definitions( -march=native -finline-functions -faggressive-loop-optimizations )
    endif() # CMAKE_BUILD_TYPE STREQUAL "Release"

    if( CMAKE_BUILD_TYPE STREQUAL "MinSizeRel" )
        set(CMAKE_CXX_FLAGS "-Os -fdata-sections -ffunction-sections")
        set(CMAKE_EXE_LINKER_FLAGS "-Wl,--gc-sections -Wl,--strip-all")  ## Strip binary
    endif()


elseif( MSVC )
        #set(MY_QT_PATH "D:/Qt/5.2.1/msvc2012_64/lib/cmake")
        #set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH} ${MY_QT_PATH}")
        #set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH} ${MY_QT_PATH}")
    add_definitions( -D_VARIADIC_MAX=10 ) # to satisfy gtest
endif()

add_subdirectory(externals)
add_subdirectory(src)


