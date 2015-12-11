TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += C++11
DEFINES += "DEBUG"

SOURCES += \
    textrender.cpp \
    vector2d.cpp \
    block.cpp \
    player.cpp \
    sam.cpp \
    movable.cpp \
    manager.cpp \
    equation.cpp \
    dan.cpp

include(deployment.pri)
qtcAddDeployment()

# LIBS += -lsfml

HEADERS += \
    ball.h \
    textrender.h \
    vector2d.h \
    block.h \
    player.h \ 
    sam.h \
    movable.h \
    manager.h \
    equation.h \
    dan.h


