QT += quick qml core gui

CONFIG += c++17
CONFIG += qt warn_on

TEMPLATE = app
TARGET = kaya-sw-camera_qa_studio

DESTDIR = $$PWD/TESTDIR

INCLUDEPATH += src

SOURCES += \
    src/main.cpp \
    src/RawPixelModel.cpp

HEADERS += \
    src/RawPixelModel.h

RESOURCES += \
    src/qml.qrc

CONFIG(debug, debug|release) {
    TARGET = $$TARGET"D"
}
