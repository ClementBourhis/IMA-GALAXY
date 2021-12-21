//STL
#include <iostream>
#include <vector>

//glimac
#include <glimac/SDLWindowManager.hpp>

//GL
#include <GL/glew.h>

//Mesh
#include <Mesh/Square.hpp>
#include <Mesh/Cube.hpp>

//Game
#include <Game/Camera.hpp>
#include <Game/Partie.hpp>

//Element
#include <Elements/Element.hpp>
#include <Elements/Skybox.hpp>

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
    const unsigned int WINDOW_WIDTH = 1920;
    const unsigned int WINDOW_HEIGHT = 1080;

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

    partie.getInfosPlateau();

    std::vector<Case> cells = partie.getMap().getCells();

    /*----------CAMERA----------*/
    Camera camera;

    std::cout << "position cam : " << camera.getPositionInScene() << std::endl;

    std::cout << "VM : " << camera.getViewMatrix() << std::endl;

    /*----------SHADERS---------*/
    FilePath vsPath = applicationPath.dirPath() + "shaders/camera.vs.glsl";
    FilePath fsPath = applicationPath.dirPath() + "shaders/camera.fs.glsl";

    ShaderManager shader(vsPath, fsPath);

    /*----------Texture----------*/
    FilePath texturePath = applicationPath.dirPath()+"../Assets/textures/Floor/sparckle.png";
    Texture texture(texturePath);

    texturePath = applicationPath.dirPath()+"../Assets/textures/test/triforce.png";
    Texture texture2(texturePath);

    texturePath = applicationPath.dirPath()+"../Assets/textures/skybox/skybox.png";
    Texture texture3(texturePath);

    /*----------MESH----------*/
    Square square;
    square.fillBuffers(); 

    Cube cube;
    cube.fillBuffers();

    /*---------ELEMENTS--------*/

    Element floor(&square, &shader, &texture);

    Element cubox(&cube, &shader, &texture2, glm::vec3(0,0.5f,0), glm::vec3(0.5, 1, 0.5));

    Skybox skybox(&cube, &shader, &texture3, camera.getPositionInScene(), glm::vec3(1, 1, 1));

    //----Transfo
    glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), WINDOW_WIDTH/(float)WINDOW_HEIGHT, 0.1f, -100.f);
    std::cout << ProjMatrix << std::endl;

    glEnable(GL_DEPTH_TEST);

    // Application loop:
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
            camera.controlManager(e);

            if(windowManager.isKeyPressed(SDLK_m)){
                std::cout << camera.getViewMatrix() << std::endl;
            }

            if(windowManager.isKeyPressed(SDLK_z)){
                cubox.translate(glm::vec3(0,0,1));
            }

            if(windowManager.isKeyPressed(SDLK_s)){
                cubox.translate(glm::vec3(0,0,-1));;
            }

            if(windowManager.isKeyPressed(SDLK_d)){
                cubox.translate(glm::vec3(-1,0,0));;
            }

            if(windowManager.isKeyPressed(SDLK_q)){
                cubox.translate(glm::vec3(1,0,0));;
            }
        }

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //-----DRAW-----
        skybox.updatePosition(camera.getPositionInScene());
        skybox.draw(ProjMatrix, camera.getViewMatrix());

        
        for(const auto &it : cells){
            floor.position() = it.getPosition();
            floor.draw(ProjMatrix, camera.getViewMatrix());
        }
        

        cubox.draw(ProjMatrix, camera.getViewMatrix());
        

        // Update the display
        windowManager.swapBuffers();
    }

    //-----LIBERATION MEMOIRE-----
    /*for(auto &it : elements){
        delete it;
    }*/
    cube.free();
    texture2.free();
    texture3.free();
    square.free();
    texture.free();

    return EXIT_SUCCESS;
}