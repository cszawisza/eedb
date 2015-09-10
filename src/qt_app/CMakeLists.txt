find_package(Qt5Widgets)
set(CMAKE_AUTOMOC OFF)

add_subdirectory(Test_modules)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Include)

FILE(GLOB SRC_FILES Source/*.cpp)
FILE(GLOB HEADER_FILES Include/*.hpp Include/*.h)
FILE(GLOB UI_FILES Forms/*.ui)

#files containing Q_OBJECT makro
set(QT_HEADERS
    Include/AddUserDialog.hpp
    Include/ApplicationMainWindow.hpp
    Include/LoginDialog.hpp
    Include/MrichTextEdit.hpp
    Include/MTextEdit.hpp
    Include/QScienceSpinBox.hpp
)

QT5_WRAP_UI(UIS_HDRS ${UI_FILES})
QT5_WRAP_CPP(GUI_MOC_SRCS ${QT_HEADERS})

add_library(client_lib ${SRC_FILES} ${HEADER_FILES} ${GUI_MOC_SRCS} ${UIS_HDRS})
add_executable( Client main.cpp)
target_link_libraries( client_lib Qt5::Widgets  )
target_link_libraries( Client Common client_lib )

add_dependencies(client_lib Common)
