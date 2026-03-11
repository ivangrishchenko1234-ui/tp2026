cmake_minimum_required(VERSION 3.10)

project(ShapesProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(lib)

add_executable(shapes_app main.cpp)

target_link_libraries(shapes_app PRIVATE shapes_lib)