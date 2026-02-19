QT += quick qml core gui

CONFIG += c++17
CONFIG += qt warn_on

TEMPLATE = app
TARGET = kaya-sw-camera_qa_studio

INCLUDEPATH += src

SOURCES += \
    src/main.cpp \
    src/RawPixelModel.cpp

HEADERS += \
    src/RawPixelModel.h

RESOURCES += \
    src/qml.qrc
