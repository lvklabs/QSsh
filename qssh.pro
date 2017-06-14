TEMPLATE  = subdirs
CONFIG   += ordered

include(qssh.pri)

SUBDIRS = \
    src \
    examples

equals(TEST, 1) {
    SUBDIRS += tests 
}
