//STL
#include <iostream>
#include <vector>

//glimac
#include <glimac/SDLWindowManager.hpp>

//GL
#include <GL/glew.h>

//Game
#include <Game/GameManager.hpp>

using namespace glimac;

int main(int argc, char** argv) {
    // Initialize SDL and open a window
    unsigned int WINDOW_WIDTH = 0;
    unsigned int WINDOW_HEIGHT = 0;
    SDLWindowManager windowManager(WINDOW_WIDTH, WINDOW_HEIGHT, "IMA'GALAXY");
    

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    /*********************************
     ****** INITIALIZATION CODE ******
     *********************************/
    FilePath applicationPath(argv[0]); // chemin du programme
    GameManager game(applicationPath.dirPath());
    //Mettre le jeu en fullscreen
    game.makeFullscreen();
    WINDOW_WIDTH = game.windowWidth();
    WINDOW_HEIGHT = game.windowHeight();
    std::cout << "Résolution : " << game.windowWidth() << " x " << game.windowHeight() << std::endl;

    std::cout << "ASSETS GAME\n" << *game.assets() << std::endl;

    /* Nombre minimal de millisecondes separant le rendu de deux images, 24 images par secondes */
    static const Uint32 FRAMERATE_MILLISECONDS = 1000 / game.framerate();

    //std::cout << game.currentPartie()->assets() << std::endl;

    //----Transfo
    glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), WINDOW_WIDTH/(float)WINDOW_HEIGHT, game.zNear(), game.zFar());

    //----profondeur
    glEnable(GL_DEPTH_TEST);

    // Application loop:
    bool done = false;
    while(!done) {
        /* Recuperation du temps au debut de la boucle */
        Uint32 startTime = SDL_GetTicks();

        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            bool isDone = game.eventManager(e);
            if(isDone){
                done = true;
            }
            if(e.type == SDL_QUIT){
                done = true; // Leave the loop after this iteration
            }
        }

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        game.draw(ProjMatrix);

        // Update the display
        windowManager.swapBuffers();

        /* Calcul du temps ecoule */
        Uint32 elapsedTime = SDL_GetTicks() - startTime;
        /* Si trop peu de temps s'est ecoule, on met en pause le programme */
        if(elapsedTime < FRAMERATE_MILLISECONDS) 
        {
            SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
        }
    }

    //-----LIBERATION MEMOIRE-----
    game.deleteGame();

    return EXIT_SUCCESS;
}