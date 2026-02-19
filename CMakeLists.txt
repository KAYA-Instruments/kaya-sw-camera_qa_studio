cmake_minimum_required(VERSION 3.21)
project(raw_twin_viewer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 6.2 REQUIRED COMPONENTS Quick)

qt_add_executable(raw_twin_viewer
    main.cpp
    RawPixelModel.h
    RawPixelModel.cpp
    qml.qrc
)



set_target_properties(raw_twin_viewer PROPERTIES OUTPUT_NAME "kaya-sw-camera_qa_studio")
target_link_libraries(raw_twin_viewer PRIVATE Qt6::Quick)
