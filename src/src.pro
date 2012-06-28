TARGET = logger

QT += xml

TEMPLATE = lib
CONFIG += dll

SOURCES += \
    logpattern.cpp \
    logmessage.cpp \
    abstractappender.cpp \
    consoleappender.cpp \
    logconfigreader.cpp

HEADERS += \
    logpattern.h \
    logmessage.h \
    abstractappender.h \
    consoleappender.h \
    logconfigreader.h


VER_MAJ = 1
VER_MIN = 0
VER_PAT = 0

include(../common.pri)
DESTDIR = $$BIN_DIR/lib
