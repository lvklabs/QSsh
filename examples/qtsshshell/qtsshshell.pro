#-------------------------------------------------
#
# Project created by QtCreator 2013-11-13T15:43:45
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtsshshell
TEMPLATE = app

QSSH_ROOT = $${PWD}/../..
DESTDIR           = $${QSSH_ROOT}/examples_bin

INCLUDEPATH = $$PWD/../../src/libs/ssh/

CONFIG += C++11

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui





include(../../qssh.pri) ## Required for IDE_LIBRARY_PATH and qtLibraryName
LIBS += -L$${QSSH_ROOT}/lib -l$$qtLibraryName(Botan) -l$$qtLibraryName(QSsh)
