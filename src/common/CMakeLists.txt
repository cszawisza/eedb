project( Common )

add_subdirectory(messages)

file(GLOB_RECURSE SRC "*.h" "*.cpp" "*.hpp" )

add_library( Common STATIC ${SRC} )

target_link_libraries( Common Messages )

