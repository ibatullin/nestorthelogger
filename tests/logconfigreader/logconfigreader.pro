#-------------------------------------------------
#
# Project created by QtCreator 2012-10-01T14:43:28
#
#-------------------------------------------------

QT       += xml testlib

QT       -= gui

TARGET = tst_logconfigreadertest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_logconfigreadertest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

include(../tests.pri)

RESOURCES += \
    resources.qrc

OTHER_FILES += \
    config.xml
