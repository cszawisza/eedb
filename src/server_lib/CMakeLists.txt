project(EEDB_SERVER)

include_directories( ../ )
include_directories( ${Common_SOURCE_DIR}/messages )
include_directories( ${Common_SOURCE_DIR} )

file(GLOB SCHEMA_SRC "sql_schema/*.h")

set(SOURCES
    main.cpp
)

set(Core_CPP
    core/acl.cpp
    core/clientcache.cpp
    core/clientconnection.cpp
    core/clientworker.cpp
    core/frameparser.cpp
    core/idatabase.cpp
    core/user.cpp
    core/server.cpp
)

set(Core_H
    core/acl.h
    core/clientcache.h
    core/clientconnection.h
    core/clientworker.h
    core/frameparser.h
    core/idatabase.h
    core/iprocessor.h
    core/user.h
    core/server.h
)

set( Utils_H
    utils/hash_passwd.h
)

add_library(eedb_lib STATIC ${SOURCES} ${Core_CPP} ${Utils_H} ${Core_H} ${SCHEMA_SRC} )
target_link_libraries(eedb_lib
    pq sqlpp-postgresql
    Common
    Qt5::Core Qt5::WebSockets
    ${PROTOBUF_LITE_LIBRARY}
)
