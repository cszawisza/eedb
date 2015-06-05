include_directories( ../../messages/cpp )
include_directories( ../core )
include_directories( sqlpp11_SOURCE_DIR )
include_directories( ${sqlpp11-connector-postgresql_SOURCE_DIR}/include )
set(HEARERS
    user.h
)

set(SOURCES
    user.cpp
)

add_library(parsers STATIC ${SOURCES} ${HEADERS} )
target_link_libraries(parsers Core Messages Qt5::Core Qt5::WebSockets)
