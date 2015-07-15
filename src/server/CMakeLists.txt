project(EEDB_SERVER)

include_directories( ../ )
include_directories( core )

include_directories( ${Common_SOURCE_DIR}    )
include_directories( ${ProtobufIncludePath}  )
include_directories( ${Externals_SOURCE_DIR} )

file(GLOB SCHEMA_SRC "sql_schema/*.h" "sql_schema/*.sql")
set(SOURCES
    main.cpp
)

set(Core_CPP
    core/auth/acl.cpp
    core/auth/action.cpp
    core/auth/implementedaction.cpp
    core/auth/privilege.cpp
    core/database/initialize.cpp
    core/database/idatabase.cpp
    core/clientcache.cpp
    core/clientconnection.cpp
    core/clientworker.cpp
    core/frameparser.cpp
    core/user.cpp
    core/server.cpp
    core/inventory.cpp
)

set(Core_H
    core/auth/acl.hpp
    core/auth/action.hpp
    core/auth/implementedaction.hpp
    core/auth/privilege.hpp
    core/database/initialize.hpp
    core/database/idatabase.h
    core/clientcache.h
    core/clientconnection.h
    core/clientworker.h
    core/frameparser.h
    core/iprocessor.h
    core/user.h
    core/server.h
    core/inventory.hpp
)

set( Utils_H
    utils/hash_passwd.h
    utils/sqlpp_helper.hpp
)

add_library(eedb_lib STATIC ${SOURCES} ${Core_CPP} ${Utils_H} ${Core_H} ${SCHEMA_SRC} )
target_link_libraries(eedb_lib
    sqlpp-postgresql pq
    Common
    Qt5::Core Qt5::WebSockets
    pq
    ${PROTOBUF_LITE_LIBRARY}
)

add_executable(EedbServer app_start.cpp)
target_link_libraries(EedbServer sqlpp-postgresql pq eedb_lib)

add_dependencies(eedb_lib Common)
