cmake_minimum_required(VERSION 3.10)

project(IMACRun)

add_definitions(-std=c++11)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)

find_package(SDL REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

# Pour gérer un bug a la fac, a supprimer sur machine perso:
set(OPENGL_LIBRARIES /usr/lib/x86_64-linux-gnu/libGL.so.1)

include_directories(${SDL_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIR} glimac/include third-party/include)

set(ALL_LIBRARIES glimac Render Game Elements Mesh ${SDL_LIBRARY} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY})

add_subdirectory(glimac)
add_subdirectory(Render)
add_subdirectory(Game)
add_subdirectory(Elements)
add_subdirectory(Test_OpenGL)
add_subdirectory(Test_Meshs)
add_subdirectory(Mesh)
