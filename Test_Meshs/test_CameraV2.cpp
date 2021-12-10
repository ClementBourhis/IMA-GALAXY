#include <glimac/SDLWindowManager.hpp>

#include <GL/glew.h>
#include <iostream>
#include <vector>

#include <Mesh/Square.hpp>
#include <Game/Partie.hpp>
#include <Game/Camera.hpp>

using namespace glimac;

int main(int argc, char** argv) {
    // Initialize SDL and open a window
    const unsigned int WINDOW_WIDTH = 800;
    const unsigned int WINDOW_HEIGHT = 600;

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

    /*----------Partie----------*/
    FilePath applicationPath(argv[0]); // chemin du programme
    std::string levelLocation = applicationPath.dirPath() + "../../Temple_Run/Game/Niveaux";
    Partie partie(levelLocation, 1);
    std::vector<Case> cells = partie.getMap().getCells();

    /*----------Camera----------*/
    Camera camera;

    /*----------SHADERS---------*/
    FilePath vsPath = applicationPath.dirPath() + "shaders/camera.vs.glsl";
    FilePath fsPath = applicationPath.dirPath() + "shaders/camera.fs.glsl";

    ShaderManager shader(vsPath, fsPath);

    shader.addUniformVariable("uTexture");
    shader.addUniformVariable("uMVPMatrix");
    shader.addUniformVariable("uMVMatrix");
    shader.addUniformVariable("uNormalMatrix");

    /*----------Texture----------*/
    FilePath texturePath = applicationPath.dirPath()+"../../Temple_Run/Assets/textures/test/fleche.jpg";
    Texture texture(texturePath);

    texture.bind();
    shader.sendUniformInt("uTexture", 0);
    texture.debind();

    /*----------MESH : Square----------*/
    Square carre(1.f, &shader, &texture);
    carre.fillBuffers();

    /*----------Transfo-------*/
    glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), WINDOW_WIDTH/(float)WINDOW_HEIGHT, 0.1f, -100.f); 
    glm::mat4 MVMatrix = camera.getViewMatrix();

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
            camera.controlManager(e);
        }


        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/

        glClear(GL_COLOR_BUFFER_BIT);
        MVMatrix = glm::mat4(1.f);

        //-----DRAW-----
        carre.bind();
        for(int i = 0; i<cells.size(); i++){
            MVMatrix = glm::translate(glm::mat4(1.f), cells[i].getPosition());
            carre.draw(ProjMatrix, MVMatrix, camera.getViewMatrix());
        }
       carre.debind();

        // Update the display
        windowManager.swapBuffers();
    }

    //-----LIBERATION MEMOIRE-----
    carre.free();

    return EXIT_SUCCESS;
}