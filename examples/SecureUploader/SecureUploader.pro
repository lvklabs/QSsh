#-------------------------------------------------
#
# Project created by QtCreator 2012-11-22T15:56:43
#
#-------------------------------------------------

QT       += core network

TARGET = SecureUploader
TEMPLATE = app

INCLUDEPATH = $$PWD/../../src/libs/ssh/

QSSH_ROOT = $${PWD}/../..
DESTDIR           = $${QSSH_ROOT}/examples_bin

SOURCES += \
    main.cpp \
    securefileuploader.cpp

HEADERS  += \
    securefileuploader.h

include(../../qssh.pri) ## Required for IDE_LIBRARY_PATH and qtLibraryName

LIBS += -L$${QSSH_ROOT}/lib -l$$qtLibraryName(Botan) -l$$qtLibraryName(QSsh)

