DESTDIR = bin

DEFINES += C11
QMAKE_CXXFLAGS += -std=c++0x

SOURCE_TREE = $$PWD

BUILD_DIR = $$SOURCE_TREE/build
OBJECTS_DIR = $$BUILD_DIR
MOC_DIR = $$BUILD_DIR

BIN_DIR = $$SOURCE_TREE/bin
