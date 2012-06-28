TARGET = logger

QT += xml

TEMPLATE = lib
CONFIG += dll

SOURCES += \
    logpattern.cpp \
    logmessage.cpp \
    abstractappender.cpp \
    consoleappender.cpp \
    logconfigreader.cpp \
    logmanager.cpp \
    logcategory.cpp \
    logger.cpp \
    nullappender.cpp \
    tracer.cpp \
    fileappender.cpp

HEADERS += \
    logpattern.h \
    logmessage.h \
    abstractappender.h \
    consoleappender.h \
    logconfigreader.h \
    logmanager.h \
    logmanager_p.h \
    logcategory.h \
    logger.h \
    logger_p.h \
    nullappender.h \
    tracer.h \
    fileappender.h


VER_MAJ = 1
VER_MIN = 0
VER_PAT = 0

include(../common.pri)
DESTDIR = $$BIN_DIR/lib
