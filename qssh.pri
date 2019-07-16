!isEmpty(QSSH_PRI_INCLUDED):error("qssh.pri already included")
QSSH_PRI_INCLUDED = 1

isEmpty(QSSH_PREFIX) {
    unix:!macx: QSSH_PREFIX = $$[QT_INSTALL_PREFIX]
}

defineReplace(cleanPath) {
    return($$clean_path($$1))
}

defineReplace(qtLibraryName) {
   unset(LIBRARY_NAME)
   LIBRARY_NAME = $$1
   CONFIG(debug, debug|release) {
      !debug_and_release|build_pass {
          mac:RET = $$member(LIBRARY_NAME, 0)_debug
              else:win32:RET = $$member(LIBRARY_NAME, 0)d
      }
   }
   isEmpty(RET):RET = $$LIBRARY_NAME
   return($$RET)
}

isEmpty(IDE_LIBRARY_BASENAME) {
    IDE_LIBRARY_BASENAME = lib
}

isEmpty(IDE_BUILD_TREE) {
    sub_dir = $$_PRO_FILE_PWD_
    sub_dir ~= s,^$$re_escape($$PWD),,
    IDE_BUILD_TREE = $$cleanPath($$OUT_PWD)
    IDE_BUILD_TREE ~= s,$$re_escape($$sub_dir)$,,
}
IDE_APP_PATH = $$IDE_BUILD_TREE/bin
macx {
    IDE_APP_TARGET   = "Qt Creator"
    IDE_LIBRARY_PATH = $$IDE_APP_PATH/$${IDE_APP_TARGET}.app/Contents/PlugIns
    IDE_LIBEXEC_PATH = $$IDE_APP_PATH/$${IDE_APP_TARGET}.app/Contents/Resources
    IDE_BIN_PATH     = $$IDE_APP_PATH/$${IDE_APP_TARGET}.app/Contents/MacOS
    copydata = 1
    isEmpty(TIGER_COMPAT_MODE):TIGER_COMPAT_MODE=$$(QSSH_TIGER_COMPAT)
    isEmpty(TIGER_COMPAT_MODE) {
        QMAKE_CXXFLAGS *= -mmacosx-version-min=10.5
        QMAKE_LFLAGS *= -mmacosx-version-min=10.5
    }
} else {
    contains(TEMPLATE, vc.*):vcproj = 1
    IDE_APP_TARGET   = qtcreator
    IDE_LIBRARY_PATH = $$IDE_BUILD_TREE/$$IDE_LIBRARY_BASENAME
    IDE_LIBEXEC_PATH = $$IDE_APP_PATH # FIXME
    IDE_BIN_PATH     = $$IDE_APP_PATH
}

QT += widgets

# Find botan2
CONFIG += link_pkgconfig
PKGCONFIG += botan-2

CONFIG += depend_includepath

LIBS += -L$$IDE_LIBRARY_PATH
LIBS += -l$$qtLibraryName(botan-2)
INCLUDEPATH += $${PWD}/src/libs/

!isEmpty(vcproj) {
    DEFINES += IDE_LIBRARY_BASENAME=\"$$IDE_LIBRARY_BASENAME\"
} else {
    DEFINES += IDE_LIBRARY_BASENAME=\\\"$$IDE_LIBRARY_BASENAME\\\"
}

#DEFINES += QT_NO_CAST_FROM_ASCII
DEFINES += QT_NO_CAST_TO_ASCII
!macx:DEFINES += QT_USE_FAST_OPERATOR_PLUS QT_USE_FAST_CONCATENATION

win32-msvc* { 
    #Don't warn about sprintf, fopen etc being 'unsafe'
    DEFINES += _CRT_SECURE_NO_WARNINGS
}
