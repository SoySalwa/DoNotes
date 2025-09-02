cmake_minimum_required(VERSION 3.10)
project(DoNotes LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)


find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

qt_add_executable(DoNotes
    src/app.cc
    src/ui/MainWindow.cc   src/ui/MainWindow.h
)

target_include_directories(DoNotes PRIVATE
    src
    src/ui
)

target_link_libraries(DoNotes PRIVATE Qt6::Core Qt6::Widgets)
