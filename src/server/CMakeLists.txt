project(EEDB_SERVER)

include_directories( ../ )
include_directories( core )

include_directories( ${Common_SOURCE_DIR} )
include_directories( ${Common_SOURCE_DIR}/DataStructures )

add_subdirectory(Tests_modules)

file(GLOB SCHEMA_SRC "sql_schema/*.h" "sql_schema/*.sql" "sql_schema/*.hpp")
set(SOURCES main.cpp )

set(Core_CPP
    core/auth/acl.cpp
    core/auth/action.cpp
    core/auth/implementedaction.cpp
    core/auth/privilege.cpp

    core/database/initialize.cpp
    core/database/idatabase.cpp
    core/database/UserHelper.cpp
    core/database/InventoryHelper.cpp
    core/database/AclHelper.cpp
    core/database/DbConnection.cpp
    core/database/CategoryHelper.cpp
    core/database/ItemHelper.cpp


    core/clientcache.cpp
    core/clientconnection.cpp
    core/clientworker.cpp
    core/iprocessor.cpp
    core/server.cpp

    core/ProcessingUnits/CategoryPU.cpp
#    core/ProcessingUnits/ItemPU.cpp
    core/ProcessingUnits/UserPU.cpp
#    core/ProcessingUnits/InventoryPU.cpp
)

set(Core_H
    core/database/config.h
)

set( Utils_H
    utils/hash_passwd.h
    utils/sqlpp_helper.hpp
    utils/LogUtils.hpp
)

add_library(eedb_lib STATIC ${SOURCES} ${Core_CPP} ${Utils_H} ${Core_H} ${SCHEMA_SRC} )
target_link_libraries(eedb_lib
    sqlpp-postgresql pq
    Common
)

add_executable(EedbServer app_start.cpp)
target_link_libraries(EedbServer sqlpp-postgresql pq eedb_lib ProtobufAdapter)

add_dependencies(eedb_lib Common ProtobufAdapter)

install( TARGETS EedbServer DESTINATION bin )

