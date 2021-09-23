include(../defaults.pri)

#you MUST include headers to subprojects, for instance like this
#"core" is not added here because it's already in defaults.pri

#INCLUDEPATH += $$PWD/../controllers

TEMPLATE = app
CONFIG += console

LIBS += -L../lib -llibcore \

SOURCES += main.cpp \
    console_controller.cpp \
    view_console.cpp

HEADERS += \
    console_controller.h \
    view_console.h
