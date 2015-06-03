add_subdirectory(core)

set(SOURCES
    main.cpp
)

add_library(eedb_lib STATIC ${SOURCES})
target_link_libraries(eedb_lib Qt5::Core Qt5::Network)
