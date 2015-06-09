project( Common )

find_package(Qt5Core )

file(GLOB_RECURSE SRC "*.h" "*.cc" "*.cpp" )
file(GLOB protos "messages/protobuf/*.proto")

add_library( Common STATIC ${SRC} ${protos})
target_link_libraries( Common ${PROTOBUF_LITE_LIBRARIES} Qt5::Core )
