find_package(Qt5Core)

add_executable(eedb main.cpp)
target_link_libraries(eedb Qt5::Core Qt5::Network eedb_lib)
