include(../defaults.pri)

TEMPLATE = lib
TARGET = libcore
DESTDIR = ../lib

HEADERS += \
    game.h \
    game_data.h \
    hexboard.h \
    hexcell.h \
    observable.h \
    observer.h \
    player.h

SOURCES += \
    game.cpp \
    hexboard.cpp \
    hexcell.cpp \
    observable.cpp \
    player.cpp
