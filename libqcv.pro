#-------------------------------------------------
#
# Project created by QtCreator 2017-10-01T20:15:18
#
#-------------------------------------------------

QT       += widgets testlib

TARGET = "qcv"
TEMPLATE = lib
CONFIG += staticlib

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

LIBQCV_ROOT = $${PWD}
SOURCE_DIR = $${LIBQCV_ROOT}/src

SOURCES += \
        $${SOURCE_DIR}/libqcv.cpp

HEADERS += \
        $${SOURCE_DIR}/libqcv.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}


DESTDIR = $${LIBQCV_ROOT}/bin

OBJECTS_DIR = $${LIBQCV_ROOT}/tmp/$${TARGET}/obj
MOC_DIR = $${LIBQCV_ROOT}/tmp/$${TARGET}/moc
UI_DIR = $${LIBQCV_ROOT}/tmp/$${TARGET}/uic

INCLUDEPATH += /usr/local/include
LIBS += -lopencv_core

