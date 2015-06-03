#-------------------------------------------------
#
# Project created by QtCreator 2014-07-19T06:53:07
#
#-------------------------------------------------

QT       += network testlib gui sql websockets


TARGET = tst_servertests
CONFIG   += console c++11
CONFIG   -= app_bundle

TEMPLATE = app


DEFINES += SRCDIR=\\\"$$PWD/\\\"

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../protocol/release/ -lprotocol
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../protocol/debug/ -lprotocol
else:unix: LIBS += -L$$OUT_PWD/../lib/ -lprotocol

LIBS += -lprotobuf-lite

INCLUDEPATH += $$PWD/../protocol
INCLUDEPATH += $$PWD/../server/DB_schema
INCLUDEPATH += $$PWD/../server

DEPENDPATH += $$PWD/../protocol
DEPENDPATH += $$PWD/../server/DB_schema
DEPENDPATH += $$PWD/../server

HEADERS += \
    tst_servertests.h \
    tst_user.h \
    tst_magazine.h \
    tst_dbschema_user.h \
    tst_dbschema_storage.h \
    tst_item.h \
    tst_itempackage.h \
    tst_dbschema_groups.h \
    tst_parameterconfig.h \
    tst_dbschema_item.h \
    tst_messagecontainer.h

SOURCES += tst_servertests.cpp \
    main.cpp \
    tst_user.cpp \
    tst_magazine.cpp \
    tst_dbschema_user.cpp \
    tst_dbschema_storage.cpp \
    tst_item.cpp \
    tst_itempackage.cpp \
    tst_dbschema_groups.cpp \
    tst_parameterconfig.cpp \
    tst_dbschema_item.cpp \
    tst_messagecontainer.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../server/release/ -lserver
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../server/debug/ -lserver
else:unix: LIBS += -L$$OUT_PWD/../lib/ -lserver

INCLUDEPATH += $$PWD/../server
DEPENDPATH += $$PWD/../server

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../server/release/libserver.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../server/debug/libserver.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../server/release/server.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../server/debug/server.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../lib/libserver.a
