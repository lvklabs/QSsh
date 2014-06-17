#-------------------------------------------------
#
# Project created by QtCreator 2012-11-22T15:56:43
#
#-------------------------------------------------

QT       += core network

TARGET = SecureUploader
TEMPLATE = app

INCLUDEPATH = $$PWD/../../include/ssh

QSSH_ROOT = $${PWD}/../..
DESTDIR           = $${QSSH_ROOT}/examples_bin

SOURCES += \
    main.cpp \
    securefileuploader.cpp

HEADERS  += \
    securefileuploader.h

unix:LIBS += -L$${QSSH_ROOT}/lib -lQSsh

win32:CONFIG(release, debug|release): LIBS += -L$${QSSH_ROOT}/lib -lQSsh
else:win32:CONFIG(debug, debug|release): LIBS += -L$${QSSH_ROOT}/lib -lQSshd
