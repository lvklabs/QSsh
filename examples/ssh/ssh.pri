QT       = core network

QTC_LIB_DEPENDS += ssh

CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app

QSSH_ROOT = $${PWD}/../..
DESTDIR   = $${QSSH_ROOT}/examples_bin

DEPENDPATH+= $$PWD/../../include
INCLUDEPATH = $$PWD/../../include

unix:LIBS += -L$${QSSH_ROOT}/lib -lQSsh

win32:CONFIG(release, debug|release): LIBS += -L$${QSSH_ROOT}/lib -lQSsh
else:win32:CONFIG(debug, debug|release): LIBS += -L$${QSSH_ROOT}/lib -lQSshd
