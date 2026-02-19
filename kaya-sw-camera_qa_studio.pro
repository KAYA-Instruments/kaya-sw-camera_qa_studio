QT += quick qml core gui

CONFIG += c++17
CONFIG += qt warn_on

TEMPLATE = app
TARGET = kaya-sw-camera_qa_studio

SOURCES += \
    main.cpp \
    RawPixelModel.cpp

HEADERS += \
    RawPixelModel.h

RESOURCES += \
    qml.qrc
