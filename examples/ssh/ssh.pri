QT += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include ($$PWD/../../src/ssh.pri)
INCLUDEPATH += $$PWD/../../src/ssh/
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app

CONFIG += c++11
