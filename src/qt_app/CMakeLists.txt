include_directories( ../messages/cpp )

find_package(Qt5Widgets)

set(CMAKE_AUTOUIC ON)

#file(GLOB SRC "*.cpp" "*.ui" "*.h")

set(SRC main.cpp
logindialog.h
logindialog.cpp
logindialog.ui
adduserdialog.cpp
adduserdialog.ui
adduserdialog.h
)

add_executable(qeedb ${SRC} )
target_link_libraries(qeedb  Messages Qt5::Widgets Qt5::WebSockets)
