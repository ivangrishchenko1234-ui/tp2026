cmake_minimum_required(VERSION 3.10)

project(shapes_lib)

add_library(shapes_lib
    rectangle.cpp
    ring.cpp
    trap.cpp
    complex.cpp
)

target_include_directories(shapes_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})