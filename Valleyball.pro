TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += C++11

SOURCES += main.cpp \
    vector2d.cpp \
    block.cpp \
    player.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    vector2d.h \
    block.h \
    player.h

