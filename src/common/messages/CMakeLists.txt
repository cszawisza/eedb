project(auto_generated)

file(GLOB SRC "pb_cpp/*.h" "pb_cpp/*.cc" )
file(GLOB protos "protobuf/*.proto")

#set(PROTOBUF_IMPORT_DIRS ${PROTOBUF_IMPORT_DIRS} protbuf )
#protobuf_generate_cpp( SRC HEAD ${protos} )

add_library( Messages STATIC ${SRC} ${HEAD} ${protos})
target_link_libraries(Messages ${PROTOBUF_LITE_LIBRARIES})
