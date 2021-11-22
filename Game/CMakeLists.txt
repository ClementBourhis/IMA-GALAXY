include_directories(include)
file(GLOB_RECURSE SRC_FILE *.cpp *.hpp)
add_library(Game ${SRC_FILE})
target_link_libraries(Game glimac)