cmake_minimum_required(VERSION 3.10)                #Version du CMake

project(IMACRun)                                    #Nom du Projet

add_definitions(-std=c++11)                         #condition de compilation

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)    #Variable CMAKE_MODULE_PATH contient le chemin du CMake

#On récupère les lib pour utiliser openGL
find_package(SDL REQUIRED)                          
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

# Pour gérer un bug a la fac:
set(OPENGL_LIBRARIES /usr/lib/x86_64-linux-gnu/libGL.so.1)

#On indique la position des includes pour récupérer les lib de third-party et de glimac 
include_directories(${SDL_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIR} glimac/include third-party/include)

#On insère dans ALL_LIBRARIES toute les libs dont on se sert (en incluant les notre)
set(ALL_LIBRARIES glimac Render ${SDL_LIBRARY} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY})

add_subdirectory(glimac)
add_subdirectory(Render)
add_subdirectory(Test_OpenGL)
