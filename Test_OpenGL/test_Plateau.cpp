#include <glimac/SDLWindowManager.hpp>
#include <glimac/TrackballCamera.hpp>

#include <GL/glew.h>
#include <iostream>
#include <vector>

#include <Mesh/Square.hpp>
#include <Game/Partie.hpp>

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


    /*-----------PLATEAU----------*/
    FilePath applicationPath(argv[0]); // chemin du programme
    std::string levelLocation = applicationPath.dirPath() + "../../Temple_Run/Game/Niveaux";
    Partie partie(levelLocation, 1);

    partie.getInfosPlateau();


    /*----------Camera----------*/
    TrackballCamera camera;

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

    /*----------Init-------*/
    glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), WINDOW_WIDTH/(float)WINDOW_HEIGHT, 0.1f, -100.f);
    glm::mat4 MVMatrix;
    std::vector<Case> cells = partie.getMap().getCells();
    for(size_t i; i<cells.size(); i++){
        std::cout << "Cell["<<i<<"] : "<< cells[i].getPosition() << std::endl;
    }
    

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

                case SDL_KEYDOWN:
                        switch(e.key.keysym.sym) {
                            case SDLK_UP:
                                std::cout << "Zoom in" << std::endl;
                                camera.moveFront(1.f);
                                break;
                            case SDLK_DOWN:
                                std::cout << "Zoom out" << std::endl;
                                camera.moveFront(-1.f);
                                break;
                            default:
                                break;
                            }
                    break;

                case SDL_MOUSEMOTION:
                    if (windowManager.isMouseButtonPressed(SDL_BUTTON_LEFT)) {
                        if (e.motion.xrel != 0) {
                            camera.rotateUp(e.motion.xrel / 1.5f);
                        }
                        if (e.motion.yrel != 0) {
                            camera.rotateLeft(e.motion.yrel / 1.5f);
                        }
                        break;
                    }
                default:
                    break;
            }
        }

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/

        glClear(GL_COLOR_BUFFER_BIT);
        //-----DRAW-----
        carre.bind();
        for(size_t i; i<cells.size(); i++){
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
