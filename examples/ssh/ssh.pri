QT += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QSSH_ROOT = $${PWD}/../..
DESTDIR   = $${QSSH_ROOT}/examples_bin

INCLUDEPATH += $$PWD/../../include
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app

CONFIG += c++11

unix:LIBS += -L$${QSSH_ROOT}/lib -lQSsh

win32:CONFIG(release, debug|release): LIBS += -L$${QSSH_ROOT}/lib -lQSsh
else:win32:CONFIG(debug, debug|release): LIBS += -L$${QSSH_ROOT}/lib -lQSshd
