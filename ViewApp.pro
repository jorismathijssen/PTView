#-------------------------------------------------
#
# Project created by QtCreator 2015-11-24T10:50:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ViewApp
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    ipccomms.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    ipccomms.h \
    ipcproto.h

FORMS    += mainwindow.ui \
    mainwindow.ui

target.files = HelloWorld
target.path = /home/debian
INSTALLS = target

OTHER_FILES +=
