#-------------------------------------------------
#
# Project created by QtCreator 2012-06-22T17:31:36
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_logpatterntest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_logpatterntest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

INCLUDEPATH += ../../src
LIBS += -L../../lib -llogger
