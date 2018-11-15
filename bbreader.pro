#-------------------------------------------------
#
# Project created by QtCreator 2014-01-09T12:48:26
#
#-------------------------------------------------

QT += widgets core network

TEMPLATE = lib
CONFIG += plugin c++14 silent

BIN_DIR = bin
OBJ_DIR = obj

DESTDIR = $$BIN_DIR
target.path = ~/.gcu/plugins
INSTALLS += target
OBJECTS_DIR = $$OBJ_DIR
UI_DIR = $$OBJ_DIR
MOC_DIR = $$OBJ_DIR
RCC_DIR = $$OBJ_DIR

SOURCES += \
    mainwindow.cpp \
    bbreaderplugin.cpp \
    EscReader.cpp

INCLUDEPATH += /usr/share/uavos/gcu/sdk/inc/
INCLUDEPATH += ../../share/tcpclient
INCLUDEPATH += ../../share/protocol

LIBS += -lprotobuf

HEADERS  += \
    /usr/share/uavos/gcu/sdk/inc/plugin_interface.h \
    mainwindow.h \
    bbreaderplugin.h \
    EscReader.h

FORMS += \
    mainwindow.ui
