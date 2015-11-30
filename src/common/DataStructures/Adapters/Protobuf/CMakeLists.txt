project( protobuf_adapter )

file(GLOB ProtoFiles "messages/*.proto")

include_directories( ${Common_SOURCE_DIR}/DataStructures/Interfaces )

PROTOBUF_GENERATE_CPP(ProtoSources ProtoHeaders ${ProtoFiles})
set( PB
    UserAdapter.cpp
    AclAdapter.cpp
)

add_library( ProtobufAdapter STATIC ${PB} ${ProtoSources} ${ProtoHeaders} ${ProtoFiles})

set(ProtobufIncludePath ${CMAKE_CURRENT_BINARY_DIR} CACHE INTERNAL "Path to generated protobuf files.")
