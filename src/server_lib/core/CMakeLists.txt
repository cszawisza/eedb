include_directories( ../ )
include_directories( sqlpp11_SOURCE_DIR )
include_directories( ${sqlpp11-connector-postgresql_SOURCE_DIR}/include )
include_directories( ${auto_generated_SOURCE_DIR}/protbuf)

find_package(Qt5websockets)

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

find_package(Qt5Widgets)
add_library(Core STATIC ${SOURCES} )
qt5_use_modules(Core Core WebSockets)

