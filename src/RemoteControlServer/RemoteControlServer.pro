QT       += core gui network widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

INCLUDEPATH += $${_PRO_FILE_PWD_}/../../libs/sockets
INCLUDEPATH += $${_PRO_FILE_PWD_}/../../libs/client
INCLUDEPATH += $${_PRO_FILE_PWD_}/../../libs/events
INCLUDEPATH += $${_PRO_FILE_PWD_}/../../config

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

LIBS += -lX11 -lXtst

SOURCES += \
    ../../libs/client/client.cpp \
    ../../libs/events/keyboard.cpp \
    ../../libs/events/mouse.cpp \
    ../../libs/sockets/sockets_functions.cpp \
    main.cpp \
    mainwindow.cpp \
    screenshot.cpp \
    serverthread.cpp

HEADERS += \
    ../../libs/client/client.h \
    ../../libs/events/keyboard.h \
    ../../libs/events/mouse.h \
    ../../libs/sockets/sockets_functions.h \
    mainwindow.h \
    screenshot.h \
    serverthread.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

VERSION = 1.0.0.1
QMAKE_TARGET_PRODUCT = RemoteControlServer
QMAKE_TARGET_COPYRIGHT = Alexei Klimovich
