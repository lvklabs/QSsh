QT       = core network

QTC_LIB_DEPENDS += ssh
include (../../qssh.pri)

macx:QMAKE_LFLAGS += -Wl,-rpath,\"$$IDE_BIN_PATH/..\"
LIBS *= -L$$IDE_LIBRARY_PATH
unix {
    QMAKE_LFLAGS += -Wl,-rpath,\"$$IDE_LIBRARY_PATH\"
}

CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app

QSSH_ROOT = $${PWD}/../../../..
DESTDIR           = $${QSSH_ROOT}/examples_bin

DEPENDPATH+=.
INCLUDEPATH+=.
