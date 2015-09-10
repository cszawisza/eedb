project( Common )
add_subdirectory(messages)
include_directories( ${ProtobufIncludePath} )

file(GLOB UTILS "utils/*.h" "utils/*.cpp" "utils/*.hpp" )

add_library( Common STATIC ${UTILS} )

target_link_libraries( Common Messages )

