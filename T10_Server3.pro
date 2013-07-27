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
    ./qCustomPlot/qcustomplot.cpp \
    qCustomPlot/graphwindow.cpp \
    qCustomPlot/writer.cpp \
    NetServer/peerwidget.cpp \
    Windows/t10servermain.cpp \
    Windows/comportwidget.cpp \
    Windows/serverwiget.cpp \
    Windows/t10tray.cpp \
    Windows/joywidget.cpp \
    Windows/aircraftwidget.cpp \
    Windows/manipulatorwidget.cpp


HEADERS  += mainwindow.h \
    NetServer/netserver.h \
    NetServer/serverthread.h \
    NetServer/tcpsocket.h \
    NetServer/mikrohttpserver.h \
    ComPort/comporttransmitter.h \
    Aircraft/aircraft.h \
    Joystick/v_joystick_adapter.h \
    ./qCustomPlot/qcustomplot.h \
    qCustomPlot/graphwindow.h \
    qCustomPlot/writer.h \
    NetServer/peerwidget.h \
    Windows/t10servermain.h \
    Windows/comportwidget.h \
    Windows/serverwiget.h \
    Windows/t10tray.h \
    Windows/joywidget.h \
    Windows/aircraftwidget.h \
    Windows/manipulatorwidget.h


FORMS    += mainwindow.ui \
    qCustomPlot/graphwindow.ui

RESOURCES += \
    T10_Server3.qrc

OTHER_FILES += \
    qtManipulator.qml
