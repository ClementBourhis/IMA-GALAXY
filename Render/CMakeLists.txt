cmake_minimum_required(VERSION 3.10)                #on indique la version utilisé

project(Render)                                     #on donne le nom du projet          
include_directories(include)                        #indique où est le doc include
file(GLOB_RECURSE SRC_FILE *.cpp *.hpp)             #on met dans SRC_FILE tout nos file
add_library(Render ${SRC_FILE})                     #on créé une répertoire dans le buid avec tous nos files
target_link_libraries(Render glimac)                #on relie glimac et notre lib (car on se sert de glimac dans Render)
target_include_directories(Render PUBLIC include)   #on dit qu'en appelant Render on regarde le répertoire include de Render