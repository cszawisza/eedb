find_package(Qt5Widgets)
#add_subdirectory(Source)
#add_subdirectory(Include)
#add_subdirectory(Forms)
add_subdirectory(Test_modules)

set(CMAKE_AUTOMOC OFF)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Include)
include_directories(${ProtobufIncludePath})

FILE(GLOB SRC_FILES Source/*.cpp)
FILE(GLOB HEADER_FILES Include/*.hpp Include/*.h)
FILE(GLOB UI_FILES Forms/*.ui)

QT5_WRAP_UI(UIS_HDRS ${UI_FILES})
QT5_WRAP_CPP(GUI_MOC_SRCS ${SRC_FILES} ${HEADER_FILES})

add_executable( Client main.cpp ${SRC_FILES} ${HEADER_FILES} ${GUI_MOC_SRCS} ${UIS_HDRS})
target_link_libraries( Client Common Qt5::Widgets Qt5::WebSockets Qt5::Core)
