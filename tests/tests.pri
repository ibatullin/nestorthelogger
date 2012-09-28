include(../common.pri)
INCLUDEPATH += $$SOURCE_TREE/src
LIBS += -L$$BIN_DIR/lib -lnestorthelogger
DESTDIR = $$BIN_DIR/tests
