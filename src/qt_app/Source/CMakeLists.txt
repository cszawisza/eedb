find_package(Qt5Widgets)
FILE(GLOB SRC_FILES *.cpp)
FILE(GLOB HEADER_FILES
     ${CMAKE_CURRENT_SOURCE_DIR}/../Header/*.h
     ${CMAKE_CURRENT_SOURCE_DIR}/../Header/*.hpp)
FILE(GLOB UI_FILES
     ${CMAKE_CURRENT_SOURCE_DIR}/../Forms/*.ui)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../Header)
include_directories(${ProtobufIncludePath})

QT5_WRAP_UI(UIS_HDRS ${UI_FILES})
QT5_WRAP_CPP(GUI_MOC_SRCS ${SRC_FILES} ${HEADER_FILES})

add_library(qt_app_lib ${SRC_FILES} ${GUI_MOC_SRCS} ${UIS_HDRS})
target_link_libraries( qt_app_lib Common Qt5::Widgets Qt5::WebSockets)
