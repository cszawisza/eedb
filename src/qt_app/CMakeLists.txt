include_directories( ${Common_SOURCE_DIR}/messages )

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

add_executable( Client ${SRC} )
target_link_libraries( Client Messages Qt5::Widgets Qt5::WebSockets)
