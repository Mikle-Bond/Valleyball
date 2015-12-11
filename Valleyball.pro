TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += C++11
DEFINES += "DEBUG"

SOURCES += \
    sfmlrender.cpp \
    vector2d.cpp \
    block.cpp \
    player.cpp \
    sam.cpp \
    movable.cpp \
    manager.cpp 

include(deployment.pri)
qtcAddDeployment()

LIBS += -lsfml

HEADERS += \
    ball.h \
    sfmlrender.h \
    vector2d.h \
    block.h \
    player.h \ 
    sam.h \
    movable.h \
    manager.h \
    equation.h


