project(auto_generated)

set(proto_packages_cpp "cpp")
set(proto_packages_python "py")

file(GLOB SRC "cpp/*.h" "cpp/*.cc" )
file(GLOB protos "protbuf/*.proto")

#set(PROTOBUF_IMPORT_DIRS ${PROTOBUF_IMPORT_DIRS} protbuf )
#protobuf_generate_cpp( SRC HEAD ${protos} )

add_library( Messages  ${SRC} ${HEAD} ${protos})
target_link_libraries(Messages ${PROTOBUF_LITE_LIBRARIES})
