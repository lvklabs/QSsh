#-------------------------------------------------
#
# Project created by QtCreator 2012-07-23T18:19:09
#
#-------------------------------------------------

QT       += core
QT       -= gui

TARGET = BotanTest
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app

QSSH_ROOT = $${PWD}/../..
DESTDIR           = $${QSSH_ROOT}/examples_bin

INCLUDEPATH = $$PWD/../../src/libs/3rdparty/botan
SOURCES += main.cpp \
    botanAES256.cpp

HEADERS += \
    botanAES256.h

include(../../qssh.pri) ## Required for IDE_LIBRARY_PATH and qtLibraryName
LIBS += -L$${QSSH_ROOT}/lib -l$$qtLibraryName(Botan)
