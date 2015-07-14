set(SOURCES
    acl.cpp
    clientcache.cpp
    clientconnection.cpp
    clientworker.cpp
    frameparser.cpp
    idatabase.cpp
    user.cpp
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
    user.h
    server.h
)

add_library(Core STATIC ${SOURCES} ${HEADERS})
target_link_libraries(Core Common sqlpp-postgresql ${PROTOBUF_LITE_LIBRARY})
qt5_use_modules(Core Core WebSockets)

