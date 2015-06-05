include_directories( ../messages/cpp )

add_subdirectory(core)
add_subdirectory(parsers)

set(SOURCES
    main.cpp
)

add_library(eedb_lib STATIC ${SOURCES})
target_link_libraries(eedb_lib Core Messages Qt5::Core Qt5::WebSockets)
