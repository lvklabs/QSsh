#-------------------------------------------------
#
# Project created by QtCreator 2012-11-22T15:56:43
#
#-------------------------------------------------

QT       += core network

TARGET = SecureUploader
TEMPLATE = app

INCLUDEPATH = $$PWD/../../src/libs/ssh/

SOURCES += \
    main.cpp \
    securefileuploader.cpp

HEADERS  += \
    securefileuploader.h

FORMS    += mainwindow.ui

include(../../qssh.pri) ## Required for IDE_LIBRARY_PATH
LIBS += -L$$IDE_LIBRARY_PATH -lBotan -lQSsh
