project(auto_generated)

file(GLOB ProtoFiles "*.proto")
PROTOBUF_GENERATE_CPP(ProtoSources ProtoHeaders ${ProtoFiles})

add_library( Messages STATIC ${ProtoSources} ${ProtoHeaders} ${ProtoFiles})

set(ProtobufIncludePath ${CMAKE_CURRENT_BINARY_DIR} CACHE INTERNAL "Path to generated protobuf files.")
