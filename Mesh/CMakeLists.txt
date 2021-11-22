include_directories(include)
file(GLOB_RECURSE SRC_FILE *.cpp *.hpp)
add_library(Mesh ${SRC_FILE})
target_link_libraries(Mesh glimac)