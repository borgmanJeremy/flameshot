cmake_minimum_required(VERSION 3.13)

project(flameshot_tests LANGUAGES CXX)

find_package(Catch2 REQUIRED)
find_package(
        Qt5
        CONFIG
        REQUIRED
        Core
        Gui
        Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_executable(test_filenamehandler)
target_sources(test_filenamehandler PRIVATE
        ../src/utils/filenamehandler.cpp
        main.cpp
        test_filenamehandler.cpp)

target_include_directories(
        test_filenamehandler
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../>
)

target_compile_features(test_filenamehandler PRIVATE cxx_std_17)

target_link_libraries(test_filenamehandler Qt5::Widgets Catch2::Catch2)

include(CTest)
include(Catch)
catch_discover_tests(test_filenamehandler)