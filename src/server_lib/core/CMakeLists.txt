include_directories( ../ )
include_directories( ../../messages/cpp )
include_directories( sqlpp11_SOURCE_DIR )
include_directories( ${sqlpp11-connector-postgresql_SOURCE_DIR}/include )
include_directories( ${auto_generated_SOURCE_DIR}/protbuf)

set(SOURCES
    acl.cpp
    clientcache.cpp
    clientconnection.cpp
    clientworker.cpp
    frameparser.cpp
    idatabase.cpp
    server.cpp
)

set(HEADERS
    acl.h
    clientcache.h
    clientconnection.h
    clientworker.h
    frameparser.h
    idatabase.h
    iprocessor.h
    server.h
)

add_library(Core STATIC ${SOURCES} )
target_link_libraries(Core Messages ${PROTOBUF_LITE_LIBRARY})
qt5_use_modules(Core Core WebSockets)

