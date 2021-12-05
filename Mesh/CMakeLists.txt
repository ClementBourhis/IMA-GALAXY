cmake_minimum_required(VERSION 3.10)                #on indique la version utilisé

project(Mesh)                                       #on donne le nom du projet          
include_directories(include)                        #indique où est le doc include
file(GLOB_RECURSE SRC_FILE *.cpp *.hpp)             #on met dans SRC_FILE tout nos file
add_library(Mesh ${SRC_FILE})                       #on créé une répertoire dans le buid avec tous nos files
target_link_libraries(Mesh glimac)                  #on relie glimac et notre lib (car on se sert de glimac dans Mesh)
target_link_libraries(Mesh Render)                  #idem pour Render
target_include_directories(Mesh PUBLIC include)     #on dit qu'en appelant Mesh on regarde le répertoire include de Mesh