add_executable(EedbServer main.cpp)
target_link_libraries(EedbServer sqlpp-postgresql pq eedb_lib)
