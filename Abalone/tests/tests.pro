include(../defaults.pri)

TEMPLATE = app
CONFIG += console

LIBS += -L../lib -llibcore

SOURCES += main.cpp \
    game_tests.cpp \
    hexboard_tests.cpp \
    hexcell_tests.cpp

HEADERS += \
    catch.hpp \
    friend_game.h \
    friend_hexboard.h
