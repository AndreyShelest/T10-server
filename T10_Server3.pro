#-------------------------------------------------
#
# Project created by QtCreator 2012-05-10T09:49:06
#
#-------------------------------------------------

QT       += core gui
QT       += network

LIBS        += -lSDL
LIBS        += -lSDLmain

TARGET = T10_Server3
TEMPLATE = app

#   git clone git://gitorious.org/qserialdevice/qserialdevice.git
unix:include(ComPort/qserialdevice/src/unix/ttylocker.pri)
#include(ComPort/qserialdevice/src/qserialdeviceenumerator/qserialdeviceenumerator.pri)
include(ComPort/qserialdevice/src/qserialdevice/qserialdevice.pri)


SOURCES += main.cpp\
        mainwindow.cpp \
    NetServer/netserver.cpp \
    NetServer/serverthread.cpp \
    NetServer/tcpsocket.cpp \
    NetServer/mikrohttpserver.cpp \
    ComPort/comporttransmitter.cpp \
    Aircraft/aircraft.cpp \
    Joystick/v_joystick_adapter.cpp \
    Settings/settingsdialog.cpp \
    datacontainer.cpp

HEADERS  += mainwindow.h \
    NetServer/netserver.h \
    NetServer/serverthread.h \
    NetServer/tcpsocket.h \
    NetServer/mikrohttpserver.h \
    ComPort/comporttransmitter.h \
    Aircraft/aircraft.h \
    Joystick/v_joystick_adapter.h \
    Settings/settingsdialog.h \
    datacontainer.h

FORMS    += mainwindow.ui \
    Settings/settingsdialog.ui

RESOURCES += \
    T10_Server3.qrc
