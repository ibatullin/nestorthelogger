TARGET = logger

QT += xml

TEMPLATE = lib
CONFIG += dll

SOURCES += \
    logpattern.cpp

HEADERS += \
    logpattern.h


VER_MAJ = 1
VER_MIN = 0
VER_PAT = 0

include(../common.pri)
DESTDIR = $$BIN_DIR/lib
