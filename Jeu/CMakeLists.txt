file(GLOB HEADER_FILES *.hpp)           #on met dans HEADER_FILES tous les hpp
file(GLOB SRC_FILES *.cpp)              #on met dans SRC_FILES tous les cpp
file(GLOB_RECURSE SHADER_FILES *.glsl)  #on met dans SHADER_FILES tous les glsl

#pour chaque cpp
foreach(SRC_FILE ${SRC_FILES})
    get_filename_component(FILE ${SRC_FILE} NAME_WE)                        #nom du fichier
    get_filename_component(DIR ${CMAKE_CURRENT_SOURCE_DIR} NAME)            #chemin de fichier
    set(OUTPUT ${DIR}_${FILE})                                              #créer un rep output
    add_executable(${OUTPUT} ${SRC_FILE} ${HEADER_FILES} ${SHADER_FILES})   #ajout d'un executable
    target_link_libraries(${OUTPUT} ${ALL_LIBRARIES})                       #relie toute les lib
endforeach()
