cmake_minimum_required(VERSION 3.24)

project(VRPMapEditorQt VERSION 1.0 LANGUAGES CXX)

if(WIN32)
    enable_language(RC)
endif()

find_package(Qt6 6.10.1 REQUIRED COMPONENTS Widgets Network OpenGLWidgets)
find_package(OpenGL REQUIRED)
qt_standard_project_setup(REQUIRES 6.10)
set(CMAKE_AUTORCC ON)

include(CTest)
add_subdirectory(VRPMapEditorQt)
