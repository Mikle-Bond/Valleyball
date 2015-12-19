TEMPLATE = app
CONFIG += debug
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += C++11
DEFINES += "DEBUG"

SOURCES += \
    rendmachine.cpp \
    textrender.cpp \
    vector2d.cpp \
    block.cpp \
    player.cpp \
    sam.cpp \
    factory.cpp \
    movable.cpp \
    manager.cpp \
    equation.cpp \
    dan.cpp

include(deployment.pri)
qtcAddDeployment()

LIBS += -lm

HEADERS += \
    ball.h \
    textrender.h \
    rendmachine.h \
#    renderinterface.h \
    vector2d.h \
    block.h \
    player.h \ 
    sam.h \
    factory.h \
    movable.h \
    manager.h \
    equation.h \
    dan.h


