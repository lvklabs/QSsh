#-------------------------------------------------
#
# Project created by QtCreator 2013-11-13T15:43:45
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtsshshell
TEMPLATE = app

INCLUDEPATH = $$PWD/../../src/libs/ssh/

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui





include(../../qssh.pri) ## Required for IDE_LIBRARY_PATH and qtLibraryName
LIBS += -L$$IDE_LIBRARY_PATH -l$$qtLibraryName(Botan) -l$$qtLibraryName(QSsh)