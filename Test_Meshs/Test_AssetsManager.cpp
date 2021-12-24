//STL
#include <iostream>
#include <vector>

//glimac
#include <glimac/SDLWindowManager.hpp>

//GL
#include <GL/glew.h>

//Game
#include <Game/Partie.hpp>
#include <Game/AssetsManager.hpp>

/* ***************************************************
Commandes pour compiler :

- aller dans le dossier Temple_Run
- cd ../build
- cmake ../Temple_Run
- make
- ./Test_OpenGL/Test_OpenGL_Temple_Run

*************************************************** */

using namespace glimac;

int main(int argc, char** argv) {
    // Initialize SDL and open a window
    const unsigned int WINDOW_WIDTH = 900;
    const unsigned int WINDOW_HEIGHT = 800;

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
    std::string levelPath = applicationPath.dirPath() + "../Assets/Niveaux";
    Partie partie(levelPath, 1);

    std::vector<Case> cells = partie.getMap().getCells();

    /*----------AssetsManager---------*/
    FilePath assetsJson = applicationPath.dirPath() + "../Assets/assets.json";
    AssetsManager assets(assetsJson);

    //----Transfo
    glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), WINDOW_WIDTH/(float)WINDOW_HEIGHT, 0.1f, -100.f);

    glEnable(GL_DEPTH_TEST);
    
    //transparence
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 

    // Application loop:
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }

            partie.eventManager(e);
        }

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Draw
        assets.element("skybox1")->updatePosition(partie.getCamera().getPositionInScene());
        assets.element("skybox1")->draw(ProjMatrix, partie.getCamera().getViewMatrix(), false);

        for(const auto &it : cells){
            assets.element("floor")->updatePosition(it.getPosition());
            assets.element("floor")->draw(ProjMatrix, partie.getCamera().getViewMatrix());
        }

        // Update the display
        windowManager.swapBuffers();
    }

    //-----LIBERATION MEMOIRE-----
    assets.unloadAssets();

    return EXIT_SUCCESS;
}