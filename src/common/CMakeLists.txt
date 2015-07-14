project( Common )

add_subdirectory(messages)

find_package(Qt5Core )
file(GLOB_RECURSE SRC "*.h" "*.cpp" "*.hpp" )

include_directories(${ProtobufIncludePath})

add_library( Common STATIC ${SRC} )
target_link_libraries( Common Messages Qt5::Core )

