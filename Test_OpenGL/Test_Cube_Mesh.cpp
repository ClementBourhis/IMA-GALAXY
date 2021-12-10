#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <vector>

//---Mesh
#include <Mesh/Mesh.hpp>
#include <Mesh/Cube.hpp>

//---glimac
#include <glimac/TrackballCamera.hpp>

#include <Game/Partie.hpp>

using namespace glimac;

int main(int argc, char** argv) {
    // Initialize SDL and open a window
    const int WINDOW_WIDTH = 2000;
    const int WINDOW_HEIGHT = 1600;
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

    Partie currentPartie("../Temple_Run/Game/Niveaux/", 1);

    /*----------SHADERS---------*/
    FilePath applicationPath(argv[0]); // chemin du programme
    FilePath vsPath = applicationPath.dirPath() + "shaders/camera.vs.glsl";
    FilePath fsPath = applicationPath.dirPath() + "shaders/camera.fs.glsl";

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

    /*----------Activation profondeur GPU----------*/
    glEnable(GL_DEPTH_TEST); 

    /*----------3D-MATRICES----------*/
    shader.addUniformVariable("uMVPMatrix");
    shader.addUniformVariable("uMVMatrix");
    shader.addUniformVariable("uNormalMatrix");
    glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f),((float)WINDOW_WIDTH/(float)WINDOW_HEIGHT), 0.1f, 100.f);
    //glm::mat4 MVMatrix = currentPartie.getCamera().getViewMatrix();
    glm::mat4 MVMatrix = glm::mat4();

    // Application loop:
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            switch (e.type) {
				case SDL_QUIT:
					done = true;
					break;
                default:
                    break;
            }
            currentPartie.eventManager(e); //se charge des events de la camera
        }

        

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //-----DRAW-----
        cube.bind();
        //cube.draw();
        cube.draw(ProjMatrix, MVMatrix, currentPartie.getCamera().getViewMatrix());
        cube.debind();

        // Update the display
        windowManager.swapBuffers();
    }

    //-----LIBERATION MEMOIRE-----
    cube.free();

    return EXIT_SUCCESS;
}
