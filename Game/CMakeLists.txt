cmake_minimum_required(VERSION 3.10)

project(Render)
include_directories(include)
file(GLOB_RECURSE SRC_FILE *.cpp *.hpp)
add_library(Game ${SRC_FILE})
target_link_libraries(Game glimac)
target_include_directories(Game PUBLIC include)