TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += C++11

SOURCES += main.cpp \
    vector2d.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    vector2d.h

