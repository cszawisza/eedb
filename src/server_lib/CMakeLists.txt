include_directories( ../common/messages )

add_subdirectory(core)
add_subdirectory(utils)

set(SOURCES
    main.cpp
)

add_library(eedb_lib STATIC ${SOURCES})
target_link_libraries(eedb_lib pq Core Messages Qt5::Core Qt5::WebSockets)
