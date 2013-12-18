include(../ssh.pri)

QT += gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET=sftpfsmodel
SOURCES+=main.cpp window.cpp \
    modeltest.cpp
HEADERS+=window.h \
    modeltest.h
FORMS=window.ui
