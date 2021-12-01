cmake_minimum_required(VERSION 3.10)

project(Render)
include_directories(include)
file(GLOB_RECURSE SRC_FILE *.cpp *.hpp)
add_library(Render ${SRC_FILE})
target_link_libraries(Render glimac)
target_include_directories(Render PUBLIC include)