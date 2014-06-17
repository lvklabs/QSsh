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
DESTDIR   = $${QSSH_ROOT}/examples_bin

INCLUDEPATH = $$PWD/../../include/ssh

CONFIG += C++11

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui


unix:LIBS += -L$${QSSH_ROOT}/lib -lQSsh

win32:CONFIG(release, debug|release): LIBS += -L$${QSSH_ROOT}/lib -lQSsh
else:win32:CONFIG(debug, debug|release): LIBS += -L$${QSSH_ROOT}/lib -lQSshd
