include(../common.pri)
INCLUDEPATH += $$SOURCE_TREE/src
LIBS += -L$$BIN_DIR/lib -llogger
DESTDIR = $$BIN_DIR/tests
