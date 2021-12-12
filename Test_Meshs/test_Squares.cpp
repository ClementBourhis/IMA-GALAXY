#include <glimac/SDLWindowManager.hpp>
#include <glimac/TrackballCamera.hpp>

#include <GL/glew.h>
#include <iostream>
#include <vector>

#include <Mesh/Square.hpp>

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

    /*----------Camera----------*/
    TrackballCamera camera;

    /*----------SHADERS---------*/
    FilePath applicationPath(argv[0]); // chemin du programme
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
    Square carre(&shader, &texture);
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

        if(windowManager.isKeyPressed(SDLK_UP)){
                camera.moveFront(0.5f);
        }
                
        if(windowManager.isKeyPressed(SDLK_DOWN)){
                camera.moveFront(-0.5f);
        }

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/

        glClear(GL_COLOR_BUFFER_BIT);
        MVMatrix = glm::mat4(1.f);

        //-----DRAW-----
        carre.bind();
        carre.draw(ProjMatrix, MVMatrix, camera.getViewMatrix());
        MVMatrix = glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 1));
        carre.draw(ProjMatrix, MVMatrix, camera.getViewMatrix());
        MVMatrix = glm::translate(glm::mat4(1.f), glm::vec3(9, 0, 2));
        carre.draw(ProjMatrix, MVMatrix, camera.getViewMatrix());
        carre.debind();

        // Update the display
        windowManager.swapBuffers();
    }

    //-----LIBERATION MEMOIRE-----
    carre.free();

    return EXIT_SUCCESS;
}
