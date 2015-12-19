TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += C++11

SOURCES += main.cpp \
    vector2d.cpp \
    block.cpp \
    player.cpp \
    sam.cpp \
    movable.cpp \
    manager.cpp \
    dan.cpp \
    equation.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    ball.h \
    vector2d.h \
    block.h \
    player.h \ 
    sam.h \
    movable.h \
    manager.h \
    equation.h \
    dan.h


