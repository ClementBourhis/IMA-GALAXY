cmake_minimum_required(VERSION 3.10)

project(Elements)
include_directories(include)
file(GLOB_RECURSE SRC_FILE *.cpp *.hpp)
add_library(Elements ${SRC_FILE})
target_link_libraries(Elements glimac)
target_link_libraries(Elements Mesh)
target_include_directories(Elements PUBLIC include)