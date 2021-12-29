#include <glimac/SDLWindowManager.hpp>

#include <GL/glew.h>
#include <iostream>
#include <vector>

#include <Mesh/Square.hpp>
#include <Game/Partie.hpp>
#include <Game/Camera.hpp>
#include <Elements/Element.hpp>

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
    std::string levelLocation = applicationPath.dirPath() + "../Assets/Niveaux";
    Partie partie(levelLocation, 1);
    std::vector<Case> cells = partie.getMap().getCells();

    /*----------Camera----------*/
    Camera camera;

    /*----------SHADERS---------*/
    FilePath vsPath = applicationPath.dirPath() + "shaders/camera.vs.glsl";
    FilePath fsPath = applicationPath.dirPath() + "shaders/camera.fs.glsl";

    ShaderManager shader(vsPath, fsPath);

    /*----------Texture----------*/
    FilePath texturePath = applicationPath.dirPath()+"../Assets/textures/test/fleche.jpg";
    Texture texture(texturePath);

    /*----------MESH : Square----------*/
    Square carre;
    carre.fillBuffers();

    /*---------ELEMENT-----------*/
    //on rassemble tout dans un element
    Element floor(&carre, &shader, &texture);

    std::cout << "Element :\n" << floor << std::endl;

    /*----------Transfo-------*/
    glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), WINDOW_WIDTH/(float)WINDOW_HEIGHT, 0.1f, -100.f); 

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

        //-----DRAW-----
        floor.draw(ProjMatrix, camera.getViewMatrix());

        // Update the display
        windowManager.swapBuffers();
    }

    //-----LIBERATION MEMOIRE-----
    floor.~Element();

    return EXIT_SUCCESS;
}