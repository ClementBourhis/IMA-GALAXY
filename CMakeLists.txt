cmake_minimum_required(VERSION 3.10)    #Version utilisé

project(IMACRun)                        #nom du projet

add_definitions(-std=c++11)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g -O2")

#Récupération des paquets nécessaire pour OpenGL/SDL
find_package(SDL REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

# Pour gérer un bug a la fac, a supprimer sur machine perso:
set(OPENGL_LIBRARIES /usr/lib/x86_64-linux-gnu/libGL.so.1)

#recherche des includes (nécessaire pour glimac et third-party)
include_directories(${SDL_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIR} glimac/include Adds/third-party/include Adds/jsoncpp/include)

#on rassemble toutes les libs qui vont être utilisé
set(ALL_LIBRARIES glimac Render Elements Mesh Game jsoncpp ${SDL_LIBRARY} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY})

#ajout des répertoirs pour les libs
add_subdirectory(glimac)
add_subdirectory(Render)
add_subdirectory(Game)
add_subdirectory(Elements)
add_subdirectory(Test_OpenGL)
add_subdirectory(Test_Meshs)
add_subdirectory(Mesh)
add_subdirectory(Adds/jsoncpp)

#on copie le répertoire assets à la source du build (pour avoir des chemins relatifs qui fonctionnent depuis n'importe quel emplacement du build)
file(COPY Assets DESTINATION .)