project( Common )

add_subdirectory(DataStructures/Adapters/Protobuf)

include_directories( ${ProtobufIncludePath} )
include_directories( ./Interfaces )

file(GLOB UTILS "utils/*.h" "utils/*.cpp" "utils/*.hpp"  )
file(GLOB DS  "DataStructures/*.*" )
file(GLOB INT "DataStructures/Interfaces/*.hpp")
file(GLOB VAL "DataStructures/Validators/*.*")
add_library( Common STATIC ${UTILS} ${INT} ${VAL} ${DS} ${Interfaces}  )

target_link_libraries( Common )

add_subdirectory(TestModules)
