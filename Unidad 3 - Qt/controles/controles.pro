#-------------------------------------------------
#
# Project created by QtCreator 2014-11-04T08:15:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = controles
TEMPLATE = app


SOURCES += main.cpp\
    dialognuevo.cpp \
        mainwindow.cpp \
    ventana.cpp

HEADERS  += mainwindow.h \
    dialognuevo.h \
    ventana.h

FORMS    += mainwindow.ui \
    dialognuevo.ui \
    ventana.ui

RESOURCES += \
    imagenes.qrc
