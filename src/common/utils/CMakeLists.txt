file(GLOB SRC "*.h" "*.cpp" )

find_package(Qt5Core)

add_library( Utils STATIC ${SRC} )
target_link_libraries( Utils Qt5::Core )
