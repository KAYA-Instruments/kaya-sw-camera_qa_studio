cmake_minimum_required(VERSION 3.21)
project(kaya_sw_camera_qa_studio LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 6.2 REQUIRED COMPONENTS Quick)

qt_add_executable(raw_twin_viewer
    src/main.cpp
    src/RawPixelModel.h
    src/RawPixelModel.cpp
    src/qml.qrc
)

target_include_directories(raw_twin_viewer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(raw_twin_viewer PRIVATE Qt6::Quick)

set_target_properties(raw_twin_viewer PROPERTIES OUTPUT_NAME "kaya-sw-camera_qa_studio")
