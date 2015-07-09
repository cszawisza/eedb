include_directories( ${Common_BINARY_DIR} )
include_directories(${ProtobufIncludePath})

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
    mrichtextedit.cpp
    mtextedit.cpp
    mrichtextedit.ui
)

add_executable( Client ${SRC} )
target_link_libraries( Client Common Qt5::Widgets Qt5::WebSockets ${PROTOBUF_LITE_LIBRARY} )
