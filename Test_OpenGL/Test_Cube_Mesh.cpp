#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <vector>

#include <Mesh/Mesh.hpp>
#include <Mesh/Cube.hpp>

using namespace glimac;

int main(int argc, char** argv) {
    // Initialize SDL and open a window
    const int WINDOW_WIDTH = 1920;
    const int WINDOW_HEIGHT = 1080;
    SDLWindowManager windowManager(WINDOW_WIDTH, WINDOW_HEIGHT, "GLImac");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/

    /*----------SHADERS---------*/
    FilePath applicationPath(argv[0]); // chemin du programme
    FilePath vsPath = applicationPath.dirPath() + "shaders/3Dtexture.vs.glsl";
    FilePath fsPath = applicationPath.dirPath() + "shaders/3Dtexture.fs.glsl";

    ShaderManager shader(vsPath, fsPath);

    /*----------Texture----------*/
    FilePath texturePath = applicationPath.dirPath()+"../../Temple_Run/Assets/textures/skybox/back.png";
    Texture texture(texturePath);

    shader.addUniformVariable("uTexture");
    texture.bind();
    shader.sendUniformInt("uTexture", 0);
    texture.debind();

    /*----------MESH----------*/
    Cube cube(1, &shader, &texture);
    cube.fillBuffers();

    /*----------3D-MATRICES----------*/
    glEnable(GL_DEPTH_TEST);
    glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), (float)(WINDOW_WIDTH/WINDOW_HEIGHT), 0.1f, 100.f);
    glm::mat4 MVMatrix = glm::translate(glm::mat4(), glm::vec3(0, 0, -5));

    // Application loop:
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
        }

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/

        glClear(GL_COLOR_BUFFER_BIT);

        //-----DRAW-----
        cube.bind();
        cube.draw(ProjMatrix, MVMatrix);
        cube.debind();

        // Update the display
        windowManager.swapBuffers();
    }

    //-----LIBERATION MEMOIRE-----
    cube.free();

    return EXIT_SUCCESS;
}
