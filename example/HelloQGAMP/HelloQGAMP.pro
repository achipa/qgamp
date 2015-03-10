TEMPLATE = app

QT += qml quick widgets

SOURCES += main.cpp \
    ../../src/googlemp.cpp

RESOURCES += qml.qrc

QMAKE_CXXFLAGS += -std=c++11

DEFINES += GMP_ID='\\"UA-48022325-2\\"'

android: QT += androidextras

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    ../../src/googlemp.h
